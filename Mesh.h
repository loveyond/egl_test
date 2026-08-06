#ifndef MESH_H
#define MESH_H

//#include <GLES2/gl2.h>
#include <GLES3/gl3.h>

// 负责画什么
// 网格

class Mesh
{
public:

    Mesh(float* vertices, int vertexCount);

    ~Mesh();


    void draw();


private:

    GLuint VAO;
    GLuint VBO;

    int vertexCount;
};



#endif

