#ifndef SPRITE_H
#define SPRITE_H

#include "Matrix4.h"

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




// 上层封装，负责“这个东西在哪里、大小多少”，是一个会移动、旋转、缩放的对象，比如：按钮

class Sprite    // 精灵(物体)
{
public:

    Sprite(float width, float height);


    void setPosition(float x, float y); //设置位置
    void setScale(float s); // 设置缩放
    void setAngle(float angle);  // 设置旋转

    void setMoveSpeed(float moveSpeed);
    void setScaleSpeed(float scaleSpeed);
    void setRotateSpeed(float rotateSpeed);


    Matrix4 getModelMatrix();


private:

    float x;
    float y;

    float width;
    float height;

    float scale;
    float angle;

    float pivotX;   // 旋转参考点
    float pivotY;

private:

    float moveSpeed;
    float scaleSpeed;
    float rotateSpeed;

    float dir;  // 为scaleSpeed服务


public:
    void update();


};





#endif

