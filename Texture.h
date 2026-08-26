
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLES3/gl3.h>

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

class Texture
{

public:

    Texture();

    bool create( int width, int height, unsigned char* data );
    
    bool update( int width, int height, unsigned char* data );

    void bind();

private:

    GLuint id;

};


#endif


