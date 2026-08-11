#include <stdio.h>
#include <string.h>

#include "EGLManager.h"


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


bool EGLManager::init( int width, int height)
{
    printf("EGL test start\n");

//    memset(&window,0,sizeof(window));

// EGL负责"在哪里画":连接显示设备  及参数

// 第一步 获取显示设备
    
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);       // 使用系统默认显示设备    ,如/dev/fb0
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

    window.width = width;
    window.height = height;

    // 4.2 创建   EGL Surface
        
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
    if(!eglMakeCurrent(
            display,
            surface,
            surface,
            context))
    {
        printf("eglMakeCurrent failed\n");
        return false;
    }    
    printf("eglMakeCurrent success\n");


// 控制swap间隔：每次 eglSwapBuffers()，至少等待一次显示刷新周期（比如30fps）
    eglSwapInterval(display, 1);

    return true;
}

/*
    swap ret=1 error=0x3000
    swap ret=0 error=0x3003
    swap ret=0 error=0x3003
*/
void EGLManager::swap()
{
    EGLBoolean ret = eglSwapBuffers(display, surface);

//    printf("swap ret=%d error=0x%x\n",
//           ret,
//           eglGetError());
}


