
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

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
    // 位置          // UV

     0,   0, 0,       0,0,
   200,   0, 0,       1,0,
     0, 200, 0,       0,1,


   200,   0, 0,       1,0,
   200, 200, 0,       1,1,
     0, 200, 0,       0,1
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
    在一个 2 × radius 的正方形里，生成一个圆的“圆心 + 圆周顶点”，每个顶点包含 x、y、z、u、v 5 个数据
    ┌────┬────┬────┬────┬────┐
    │ x  │ y  │ z  │ u  │ v  │
    └────┴────┴────┴────┴────┘
*/
std::vector<float> createCircle(float radius, int segments)
{
    std::vector<float> vertices;

    float centerX = radius;
    float centerY = radius;

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


int main()
{


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
    
    std::vector<float> circleVertices = createCircle(100, 32);
    Mesh circle(
        circleVertices.data(),
        circleVertices.size() / 5,
        GL_TRIANGLE_FAN);    
        
    // 把 CPU 里的 RGB 图片数据，创建成 GPU 里的 2D Texture
    Texture texture;
    texture.create(2,2,image);      // 创建一张 2×2 的 RGB 图片纹理. image --> GPU Texture

// 创建sprite
//    Sprite box1(200,200);
//    Sprite box2(200,200);
    Sprite box1(&quad, 200, 200);
    Sprite box2(&circle, 50, 50);

    box1.setPosition(100,100);
    box1.setMoveSpeed(0);
    box1.setTexture(&texture);
    
    box2.setPosition(500,300);
    box2.setScaleSpeed(0);
    box2.setColor(1, 1, 0, 1);


// MVP    
//    Matrix4 view = Matrix4::translate(-1,0,0);
//    Matrix4 projection = Matrix4::ortho( 0, 1024, 600, 0, -1, 1 );
//
//    Matrix4 model;
//    Matrix4 MVP;

        
    while(1){
        gl_renderer.clear();                // 清屏
        gl_renderer.begin();                // 使用Shader

//        texture.bind();                     // 绑定Texture
        
        box1.update();                      // 更新Sprite
        box2.update();

//        model = box1.getModelMatrix();      // 绘制box1               
//        MVP = projection * view * model;        
//        gl_renderer.draw( &quad, MVP, textureState );
//
//        model = box2.getModelMatrix();      // 绘制box2
//        MVP = projection * view * model;        
//        gl_renderer.draw( &circle, MVP, whiteState );
        gl_renderer.draw(box1);
        gl_renderer.draw(box2);
        
        egl.swap();                         // 显示

//        usleep(10000);
    }





    return 0;
}



