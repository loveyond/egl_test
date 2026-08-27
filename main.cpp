
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <csignal>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <vector>
#include <cmath>


#include "GLRenderer.h"
#include "Matrix4.h"
#include "Sprite.h"
#include "Mesh.h"
#include "EGLManager.h"
#include "Texture.h"
#include "CameraEngine.h"
#include "FrameBuffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


/*
                应用层
                Sprite
                  |
            -----------------
            |               |
          Mesh          Texture
            |               |
            -----------------
                  |
          GLRenderer + Shader
                  |
                  |
              OpenGL ES
                  |
                  |
             EGLManager
                  |
                  |
              LCD显示
*/

/*
    初始化流程：初始化EGL  -> 初始化Renderer / Shader -> 创建 GPU 资源(VAO、VBO)Mesh / Texture -> 创建 Sprite -> 准备 Camera / MVP 

*/

/*
    OpenGL ES绘制流程:
        CPU代码 ->   顶点数据 -> Vertex Shader(顶点着色器) -> 三角形装配 -> Rasterization(光栅化) 
        -> Fragment Shader(片段着色器) -> Framebuffer -> LCD

*/


/*
float vertices[] =
{
     0,  0,  0,
   200,  0,  0,
     0,200,  0,

   200,  0,  0,
   200,200,  0,
     0,200,  0
};
*/
float rectangleVertices[] =
{
    //                // UV

   0,   0, 0,       0,0,
   1,   0, 0,       1,0,
     0, 1, 0,       0,1,


   1,   0, 0,       1,0,
   1, 1, 0,       1,1,
     0, 1, 0,       0,1
};


unsigned char image[] =
{
    255,0,0,
    0,255,0,

    0,0,255,
    255,255,0
};

RenderState textureState = {
    {1, 1, 1, 1},
    true
};

RenderState whiteState = {
    {1, 1, 1, 1},
    false
};

RenderState redState = {
    {1, 0, 0, 1},
    false
};


/*
    在一个 1 × 1 的正方形里，生成一个圆的“圆心 + 圆周顶点”，每个顶点包含 x、y、z、u、v 5 个数据
    ┌────┬────┬────┬────┬────┐
    │ x  │ y  │ z  │ u  │ v  │
    └────┴────┴────┴────┴────┘
*/
std::vector<float> createCircle(int segments)
{
    std::vector<float> vertices;

    const float centerX = 0.5f;
    const float centerY = 0.5f;
    const float radius = 0.5f;

    // 圆心
    vertices.push_back(centerX);
    vertices.push_back(centerY);
    vertices.push_back(0.0f);
    vertices.push_back(0.5f);       // 圆心的uv也是纹理的中心
    vertices.push_back(0.5f);       // 圆心的uv也是纹理的中心

    // 圆周
    for(int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * M_PI * i / segments;

        float x = centerX + radius * cosf(angle);
        float y = centerY + radius * sinf(angle);

        float u = (x - centerX) / (2.0f * radius) + 0.5f;
        float v = (y - centerY) / (2.0f * radius) + 0.5f;

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
        vertices.push_back(u);
        vertices.push_back(v);
    }

    return vertices;
}


struct ImageFrame
{
    unsigned char* img;
    int w;
    int h;
    int ch;
};

int jpg2rgb(ImageFrame &image)
{
    image.img = stbi_load(
        "f_20260820_173757.jpg",
        &image.w,
        &image.h,
        &image.ch,
        3
    );
    
    if(!image.img)
    {
        printf("stbi_load failed: %s\n", stbi_failure_reason());
        return -1;
    }
    
    printf("image: %d x %d channels=%d\n", image.w, image.h, image.ch);
    return 0;
}



int main()
{
    signal(SIGINT, SIG_DFL);

    FrameBuffer frameBuffer;
    CameraEngine cameraEngine(&frameBuffer);
    cameraEngine.init();


    EGLManager egl;
    egl.init(1024,600);
    printf("GL:%s\n", glGetString(GL_VERSION));


// 下面是OpenGL渲染层(GLRenderer Mesh Sprite等)    
// Renderer / Shader
    GLRenderer gl_renderer;
    gl_renderer.init();


// Mesh / Texture
    // 创建GPU资源(VAO、VBO)
    Mesh quad(rectangleVertices,6);  // 创建矩形Mesh
    
    std::vector<float> circleVertices = createCircle(32);
    Mesh circle(
        circleVertices.data(),
        circleVertices.size() / 5,
        GL_TRIANGLE_FAN);    
        
    // 把 CPU 里的 RGB 图片数据，创建成 GPU 里的 2D Texture
    Texture texture;
    ImageFrame imageFrame;
    jpg2rgb(imageFrame);
    texture.create(imageFrame.w,imageFrame.h,imageFrame.img);
    stbi_image_free(imageFrame.img);

    YUVTexture cameraTexture;


// 创建sprite
    Sprite camera1(&quad, 320, 200);
    camera1.setPosition(1024/2,600/2);
    camera1.setMoveSpeed(2);
    camera1.setScaleSpeed(0);
    camera1.setRotateSpeed(0);
    camera1.setYUVTexture(&cameraTexture);

    Sprite photo1(&quad, 200, 200);
    photo1.setPosition(100,100);
    photo1.setMoveSpeed(0);
    photo1.setScaleSpeed(0);
    photo1.setRotateSpeed(2);
    photo1.setTexture(&texture);

    Sprite circle1(&circle, 0.1, 0.1);  // 设置父子关系后的坐标已经不是坐标了,目前只用于测试,现阶段懒得改了. 0.1*0.1==(0.1*200)*(0.1*200)像素
    circle1.setParent(&camera1);         // 设置父子关系
    circle1.setPosition(0.7,0);         // 这里的位置坐标是相对于photo1的坐标: 0.7*0==(0.7*200)*0像素
    circle1.setScaleSpeed(0);
    circle1.setRotateSpeed(0);
    circle1.setColor(1, 1, 0, 1);
    circle1.setMoveSpeed(0);
    circle1.setOrbit(0.7f, 0.02f);


// MVP被封装进了renderer    

    while(1){

    
        gl_renderer.clear();                // 清屏
        gl_renderer.begin();                // 使用Shader

        
        photo1.update();                      // 更新Sprite
        circle1.update();
        camera1.update();
        camera1.updateCamera(cameraEngine);


        gl_renderer.draw(photo1);
        gl_renderer.draw(circle1);
        gl_renderer.draw(camera1);

        
        egl.swap();                         // 显示

    }

    return 0;
}



