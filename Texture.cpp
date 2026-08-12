#include <stdio.h>
#include <stdlib.h>


#include "Texture.h"


Texture::Texture()
{
    id = 0;
}


bool Texture::create( int width, int height, unsigned char* data)
{

    glGenTextures( 1, &id);

    printf("texture id=%d\n", id);
    
    glBindTexture( GL_TEXTURE_2D, id);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        data);

    glBindTexture( GL_TEXTURE_2D, 0);

    
    return true;
}



void Texture::bind()
{
    glBindTexture( GL_TEXTURE_2D, id);
}

