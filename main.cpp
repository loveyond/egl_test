
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "GLRenderer.h"
#include "Matrix4.h"
#include "Sprite.h"
#include "Mesh.h"
#include "EGLManager.h"

/*
    流程：程序  -> EGLDisplay -> libEGL.so -> Mali GPU驱动 -> /dev/fb0 -> lcd

*/

/*
    OpenGL ES绘制流程:
        CPU代码 ->   顶点数据 -> Vertex Shader(顶点着色器) -> 三角形装配 -> Rasterization(光栅化) 
        -> Fragment Shader(片段着色器) -> Framebuffer -> LCD

*/



float vertices[] =
{
     0,  0,  0,
   200,  0,  0,
     0,200,  0,

   200,  0,  0,
   200,200,  0,
     0,200,  0
};




int main()
{


    EGLManager egl;
    egl.init(1024,600);
    printf("GL:%s\n", glGetString(GL_VERSION));

// 下面是OpenGL渲染层(GLRenderer Mesh Sprite等)    
// 第七步：绘画
    GLRenderer gl_renderer;
    gl_renderer.init();




// MVP
    Matrix4 model;
    Matrix4 view;
    Matrix4 projection;
    Matrix4 MVP;

    Sprite box1(200,200);
    Sprite box2(200,200);

    box1.setPosition(100,100);
    box1.setMoveSpeed(0);
    box2.setPosition(500,300);
    box2.setScaleSpeed(0);
//    box2.setMoveSpeed(0);

    view = Matrix4::translate(-1,0,0);
    projection =
        Matrix4::ortho( 0, 1024, 600, 0, -1, 1 );

    Mesh quad(vertices,6);  // 创建矩形Mesh



        
    while(1){
        gl_renderer.clear();
        gl_renderer.begin();

        box1.update();
        box2.update();

        model = box1.getModelMatrix();                            
        MVP = projection * view * model;        
        gl_renderer.draw( &quad, MVP );

        model = box2.getModelMatrix();
        MVP = projection * view * model;        
        gl_renderer.draw( &quad, MVP );

                
//        eglSwapBuffers(display,surface);
        egl.swap();

//        usleep(10000);
    }





    return 0;
}



