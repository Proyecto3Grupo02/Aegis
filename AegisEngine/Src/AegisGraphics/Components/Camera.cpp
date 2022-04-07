
#include "Camera.h"
#include <OgreSceneManager.h>
#include <OgreViewport.h>

AegisCamera::AegisCamera(std::string camName,Ogre::SceneNode* node, bool maincam): 
	mNode_(node), mngr(node->getCreator()), isMainCam_(maincam)
{
	
	mCamera_ = mngr->createCamera(camName);
	mNode_->attachObject(mCamera_);
}

AegisCamera::~AegisCamera()
{
	mNode_->detachAllObjects();
	mngr->destroyCamera(mCamera_);
}

Ogre::Matrix4 AegisCamera::getProjectionMatrix()
{
	return mCamera_->getProjectionMatrix();
}

Ogre::Matrix4 AegisCamera::getViewMatrix()
{
	return mCamera_->getViewMatrix();
}

void AegisCamera::setViewport(double left, double top, double w, double h)
{
	mCamera_->getViewport()->setDimensions(left, top, w, h);
}

Ogre::Viewport* AegisCamera::getViewport()
{
	return mCamera_->getViewport();
}

void AegisCamera::setClipDistances(double near, double far)
{
	mCamera_->setNearClipDistance(near);
	mCamera_->setFarClipDistance(far);
}

Ogre::Camera* AegisCamera::GetCamera()
{
	return mCamera_;
}
