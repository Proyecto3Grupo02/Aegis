#include <OgreCamera.h>


class AegisCamera
{
private:
    Ogre::Camera* mCam_;
public:
    AegisCamera(/* args */);
    ~AegisCamera();

    void lookAt(float x, float y, float z);
    void setDirection(float x, float y, float z);


    

};

AegisCamera::AegisCamera(/* args */)
{
}

AegisCamera::~AegisCamera()
{
}
