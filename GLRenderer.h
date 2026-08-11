#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "Matrix4.h"
#include "Mesh.h"
#include "Shader.h"

/*
    应用层
      |
   Sprite
      |
   Mesh
      |
 GLRenderer
      |
 OpenGL ES
      |
 EGLManager
      |
Linux Display
*/

// GLRenderer 负责怎么把它画出来，操作 OpenGL 的
class GLRenderer
{

public:

    bool init();

    void draw( Mesh* mesh, Matrix4& mvp);

    void clear();

    void begin();
private:

//    static char *loadFile(const char *filename);
//    static GLuint loadShader( GLenum type, const char *source);


private:

    GLuint program;
    GLuint VBO;
    GLuint texture;
    GLint colorLoc;

    GLint mvpLoc;     // 矩阵

//    GLint offsetLoc;
    GLint pos;
    
    char *vertexSource;
    char *fragmentSource;

    Shader shader;

};

#endif


