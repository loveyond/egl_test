
#include "CameraEngine.h"


CameraEngine::CameraEngine(FrameBuffer* buffer)
{
    frameBuffer = buffer;
    
    camera = new CameraV4L2(2,1280,720);
}

CameraEngine::~CameraEngine()
{
    delete camera;
}


bool CameraEngine::init()
{
    if(!camera->openDevice())
        return false;

    camera->setFmt();

    camera->reqBufs();

    camera->startCapture();

    return true;
}


bool CameraEngine::capture(Frame& frame)
{
//    Frame frame;

//    if(camera->getFrame(frame))
//    {
//        frameBuffer->update(frame);
//    }

    return camera->getFrame(frame);

}



