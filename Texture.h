
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLES3/gl3.h>


class Texture
{

public:

    Texture();

    bool create( int width, int height, unsigned char* data );

    void bind();

private:

    GLuint id;

};


#endif


