
#include "Sprite.h"



// 精灵(物体)

Sprite::Sprite(float width,float height)
{
    this->width = width;
    this->height = height;

    x = 0;
    y = 0;

    scale = 1.0f;
    angle = 0;
    
    dir = 1.0f;
    moveSpeed = 5.0f;
    scaleSpeed = 0.01f;
    rotateSpeed = 1.0f;


    pivotX = width / 2.0f;
    pivotY = height / 2.0f;
}


void Sprite::setPosition(float x,float y)
{
    this->x = x;
    this->y = y;
}


void Sprite::setScale(float s)
{
    scale = s;
}


void Sprite::setAngle(float angle)
{
    this->angle = angle;
}

void Sprite::setMoveSpeed(float moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void Sprite::setScaleSpeed(float scaleSpeed)
{
    this->scaleSpeed = scaleSpeed;
}
void Sprite::setRotateSpeed(float rotateSpeed)
{
    this->rotateSpeed = rotateSpeed;
}



Matrix4 Sprite::getModelMatrix()
{
    return
        Matrix4::translate(x,y,0) *
        Matrix4::translate(pivotX,pivotY,0) *   // // 然后恢复原来的中心
        Matrix4::rotate(angle) *
        Matrix4::scale(scale,scale,1) *
        Matrix4::translate(-pivotX,-pivotY,0);  // 先把旋转中心移动到原点
}

void Sprite::update()
{
    x += moveSpeed;
    if(x >= 1024)
        x = -width;


    scale += scaleSpeed  * dir;
    if(scale >= 1.5f)
    {
        scale = 1.5f;
        dir = -1.0f;
    }
    else if(scale <= 0.1f)
    {
        scale = 0.1f;
        dir = 1.0f;
    }


    angle += rotateSpeed;
    if(angle >= 360)
        angle = 0;
}


