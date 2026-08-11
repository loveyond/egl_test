
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

static EGLint attribs[] =
{
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,           // 创建 窗口Surface

    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,    // 用OpenGL ES 2.0

    EGL_RED_SIZE, 8,                            // RGB888
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,

    EGL_NONE
};

static EGLint contextAttribs[] =
{
    EGL_CONTEXT_CLIENT_VERSION,         // OpenGL ES 2.0
    2,
    EGL_NONE
};

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
/*
    printf("EGL test start\n");

// 第一步 获取显示设备
    EGLDisplay display;     // EGL 和底层显示系统的连接句柄
    
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);       // 使用系统默认显示设备    
    if(display == EGL_NO_DISPLAY)
    {
        printf("eglGetDisplay failed\n");
        return -1;
    }
    printf("eglGetDisplay success\n");

    EGLint major;
    EGLint minor;

// 第二步 初始化 EGL
    if(!eglInitialize(display, &major, &minor))
    {
        printf("eglInitialize failed\n");
        return -1;
    }
    printf("EGL version %d.%d\n", major, minor);    // 版本 EGL 1.4

// 第三步 选择 EGL 配置
    EGLConfig config;
    EGLint num_config;

    if(!eglChooseConfig(
            display,
            attribs,
            &config,
            1,
            &num_config))
    {
        printf("eglChooseConfig failed\n");
        return -1;
    }
    printf("config count=%d\n", num_config);

// 第四步 创建显示窗口：[ EGL_DEFAULT_DISPLAY(/dev/fb0)和 EGL 的连接 ]
    // 4.1 创建 fbdev_window
    fbdev_window window;

    window.width = 1024;
    window.height = 600;

    // 4.2 创建   EGL Surface
    EGLSurface surface;
        
    surface = eglCreateWindowSurface(
            display,
            config,
            &window,
            NULL
    );        
    if(surface == EGL_NO_SURFACE)
    {
        printf("eglCreateWindowSurface failed\n");
        return -1;
    }
    printf("surface create success\n");

// 第五步：创建 GLES2 Context        
    EGLContext context;     // OpenGL ES 的运行环境
    
    context = eglCreateContext(
            display,
            config,
            EGL_NO_CONTEXT,
            contextAttribs
    );    
    
    if(context == EGL_NO_CONTEXT)
    {
        printf("eglCreateContext failed\n");
        return -1;
    }
    printf("context create success\n");

// 第六步：绑定
    eglMakeCurrent(
        display,
        surface,
        surface,
        context
    );
*/

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



