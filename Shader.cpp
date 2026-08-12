#include <stdio.h>
#include <stdlib.h>

#include "Shader.h"


bool Shader::load( const char* vertexFile, const char* fragmentFile)
{

    char* vertexSource = loadFile(vertexFile);

    char* fragmentSource = loadFile(fragmentFile);
    
    //第3步： Shader编译    
    GLuint vs = loadShader( GL_VERTEX_SHADER, vertexSource);
    GLuint fs = loadShader( GL_FRAGMENT_SHADER, fragmentSource);

    //第4步： 创建program
    program = glCreateProgram();
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);


    GLint success;    
    glGetProgramiv( program, GL_LINK_STATUS, &success);    
    printf("program link=%d\n",success);    
    if(!success)
    {
        char log[512];    
        glGetProgramInfoLog(
            program,
            sizeof(log),
            NULL,
            log);    
        printf("link error:%s\n",log);
    }


    return true;
}

char *Shader::loadFile(const char *filename)
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


GLuint Shader::loadShader( GLenum type, const char *source)
{
    GLuint shader;

    shader = glCreateShader(type);

    glShaderSource( shader, 1, &source, NULL );

    glCompileShader(shader);


    GLint success;    
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success);
    printf("shader compile=%d\n",success);
    if(!success)
    {
        char log[512];
        glGetShaderInfoLog(
            shader,
            sizeof(log),
            NULL,
            log);
        printf("shader error:%s\n",log);
    }


    return shader;
}


