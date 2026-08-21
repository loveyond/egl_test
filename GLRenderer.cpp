

#include <stdio.h>
#include <stdlib.h>

#include "GLRenderer.h"

/*
OpenGL ES自己的坐标系统,顶点坐标范围：x: -1 ~ +1        ，y: -1 ~ +1，z:0，纹理坐标范围： 0~1
    float vertices[] =
    {
        -1.0f,  1.0f, 0.0f,   // lcd左上角
         1.0f,  1.0f, 0.0f,   // lcd右上角
        -1.0f, -1.0f, 0.0f,   // lcd左下角
         1.0f, -1.0f, 0.0f,   // lcd右下角
         0,0,0                // lcd正中心
    };    
*/

//    float vertices[] =
//    {
//        -0.5f,  0.5f, 0.0f,   // 左上
//         0.5f,  0.5f, 0.0f,   // 右上
//        -0.5f, -0.5f, 0.0f,   // 左下
//    
//         0.5f,  0.5f, 0.0f,   // 右上
//         0.5f, -0.5f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f    // 左下
//    };

//    float vertices[] =
//    {
//         0,  0,  0,
//       200,  0,  0,
//         0,200,  0,
//    
//       200,  0,  0,
//       200,200,  0,
//         0,200,  0
//    };


// 负责怎么把它画出来

bool GLRenderer::init()
{

    shader.load( "texture_vertex.glsl",       // 顶点着色器代码
        "texture_fragment.glsl" );             // 片元着色器代码

    program = shader.getProgram();
    printf("program=%d\n",program);


    // 控制矩形移动、缩放、旋转、颜色等
    colorLoc = glGetUniformLocation(program,"color");
    printf("colorLoc=%d\n",colorLoc);

    useTextureLoc = glGetUniformLocation(program,"useTexture");
    printf("useTextureLoc=%d\n",useTextureLoc);
    
    mvpLoc = glGetUniformLocation(program,"MVP");   // 矩阵
    printf("mvpLoc=%d\n",mvpLoc);
    
    textureLoc = glGetUniformLocation(program,"texture0");
    printf("textureLoc=%d\n",textureLoc);

    projection = Matrix4::ortho(0, 1024, 600, 0, -1, 1);
    view = Matrix4::translate(-1, 0, 0);

    
    return true;
}



void GLRenderer::draw( Sprite& sprite)
{
    
    Matrix4 model = sprite.getModelMatrix();

    Matrix4 mvp = projection * view * model;

    const RenderState& state = sprite.getRenderState();

    glUniform4f(colorLoc, state.color.r, state.color.g, state.color.b, state.color.a);
    
    glUniformMatrix4fv( mvpLoc, 1, GL_FALSE, mvp.m );
//    glUniform1i(textureLoc,0);
    glUniform1i(useTextureLoc, state.useTexture ? 1 : 0);

    if(sprite.getTexture())
    {
        sprite.getTexture()->bind();
        glUniform1i(textureLoc, 0);         // texture0 应该去 第 0 个 Texture Unit(不是 Texture ID) 取数据
    }
    
    sprite.getMesh()->draw();

}

void GLRenderer::clear()
{
    glClear( GL_COLOR_BUFFER_BIT );
}

void GLRenderer::begin()
{
    glUseProgram(program);
}





