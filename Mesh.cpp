
#include "Mesh.h"

// 负责画什么
// 网格
Mesh::Mesh(float* vertices,int count)
{
    vertexCount = count;

//第1步： 获取顶点数据vertices

//第2步：创建VAO ,Vertex Array Object，顶点数组对象
//       创建VBO(把CPU的数据上传到GPU),Vertex Buffer Object（顶点缓冲对象）
    glGenVertexArrays(1,&VAO);  // 创建一个空的 VAO
    glBindVertexArray(VAO);     // 绑定这个 VAO，告诉 OpenGL 开始记录状态,接下来所有跟顶点相关的设置，都记到这个 VAO 里面

    glGenBuffers(1,&VBO);
    glBindBuffer( GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        count*3*sizeof(float),
        vertices,
        GL_STATIC_DRAW);

//第5步： 告诉GPU顶点格式位置
    glVertexAttribPointer(
        0,              // 第0号顶点属性，从当前VBO读取。对应:layout(location=0) in vec3 position;
        3,
        GL_FLOAT,
        GL_FALSE,
        3*sizeof(float),
        0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);       // 解绑 VAO，结束记录

}




Mesh::~Mesh()
{
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
}



void Mesh::draw()
{
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);     // 绑定VAO
    
    glDrawArrays(               // 设置
        GL_TRIANGLES,
        0,
        vertexCount
    );

//    glBindVertexArray(0);       // 解绑

}





