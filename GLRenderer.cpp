

#include <stdio.h>
#include <stdlib.h>

#include "GLRenderer.h"



// 负责怎么把它画出来

bool GLRenderer::init()
{
    vertexSource = loadFile("vertex.glsl");       // 顶点着色器代码
    fragmentSource = loadFile("fragment.glsl");   // 片元着色器代码

//第1步： 顶点数据
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
//        // position        // texture
//    
//        -0.5f, 0.5f,0,     0,0,
//         0.5f, 0.5f,0,     1,0,
//        -0.5f,-0.5f,0,     0,1,
//    
//         0.5f,0.5f,0,      1,0,
//         0.5f,-0.5f,0,     1,1,
//        -0.5f,-0.5f,0,     0,1
//    };

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



//第2步： 创建VBO(把CPU的数据上传到GPU),Vertex Buffer Object（顶点缓冲对象）
//    glGenBuffers( 1, &VBO );
//    glBindBuffer( GL_ARRAY_BUFFER, VBO );
//    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

//第3步： Shader编译    
    GLuint vs =
        loadShader(
            GL_VERTEX_SHADER,
            vertexSource );
    GLuint fs =
        loadShader(
            GL_FRAGMENT_SHADER,
            fragmentSource );

//第4步： 创建program
    program = glCreateProgram();
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);



//第5步： 告诉GPU顶点格式位置
//    pos = glGetAttribLocation( program, "position" );
//    glBindBuffer( GL_ARRAY_BUFFER, VBO );
//    glVertexAttribPointer(
//        pos,
//        3,
//        GL_FLOAT,
//        GL_FALSE,
//        3*sizeof(float),
//        0 );
//    glEnableVertexAttribArray(pos);


    // 控制矩形移动、缩放、旋转、颜色
    colorLoc = glGetUniformLocation(program,"color");
    printf("colorLoc=%d\n",colorLoc);
    mvpLoc = glGetUniformLocation(program,"MVP");   // 矩阵

    return true;
}

// 单位矩阵
//static float matrix[16] =
//{
//    1,0,0,0,
//    0,1,0,0,
//    0,0,1,0,
//    0,0,0,1
//};

void GLRenderer::draw( Mesh* mesh, Matrix4& mvp)
{
    
    glUniform4f(colorLoc,1.0,0.0,1.0,1.0);
    glUniformMatrix4fv( mvpLoc, 1, GL_FALSE, mvp.m );

    mesh->draw();

}

void GLRenderer::clear()
{
    glClear( GL_COLOR_BUFFER_BIT );
}

void GLRenderer::begin()
{
    glUseProgram(program);
}


char *GLRenderer::loadFile(const char *filename)
{
    FILE *fp = fopen(filename, "rb");

    if(!fp)
    {
        printf("open %s failed\n", filename);
        return NULL;
    }


    fseek(fp, 0, SEEK_END);

    long size = ftell(fp);

    rewind(fp);


    char *buffer = (char *)malloc(size + 1);

    fread(buffer, 1, size, fp);

    buffer[size] = '\0';


    fclose(fp);

    return buffer;
}


GLuint GLRenderer::loadShader( GLenum type, const char *source)
{
    GLuint shader;

    shader = glCreateShader(type);

    glShaderSource( shader, 1, &source, NULL );

    glCompileShader(shader);

    return shader;
}



