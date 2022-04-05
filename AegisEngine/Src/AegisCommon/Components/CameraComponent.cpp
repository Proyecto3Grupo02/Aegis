#include "CameraComponent.h"
#include "../Entity/Entity.h"
CameraComponent::CameraComponent(Entity* ent, std::string name, bool isMainCam):
	AegisComponent("Camera", ent), mCamera_(nullptr), isMainCam_(isMainCam)
{
	mCamera_ = new AegisCamera(name, getEntity()->getNode(), getEntity()->getNode()->getCreator(), isMainCam);
	tr_ = getEntity()->GetTransform();
}

CameraComponent::~CameraComponent()
{
	delete mCamera_;
}

void CameraComponent::lookAt(float x, float y, float z,SpaceReference mRef)
{
	switch (mRef) {
	case SpaceReference::LOCAL:
		mNode_->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_LOCAL);
		break;
	case SpaceReference::PARENT:

		mNode_->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_PARENT);
		break;	
	case SpaceReference::WORLD:

		mNode_->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_WORLD);
		break;	
	}
}

Vector3 CameraComponent::getDirection() const
{
	auto direction = mNode_->getOrientation().zAxis() * -1;

	Vector3 dir = Vector3(dir.x, dir.y, dir.z);

	return dir;
}

Quaternion CameraComponent::getOrientation() const
{
	return mOrientation_;

}

void CameraComponent::setDirection(Vector3 dir)
{
	mNode_->setDirection(dir.x, dir.y, dir.z);
}

void CameraComponent::setOrientation(const Quaternion& orientation)
{
	mOrientation_ = orientation;
	tr_->SetRotation(orientation);
}

Vector3 CameraComponent::worldToScreen(const Vector3& worldPoint)
{
	Ogre::Vector3 world;
	world.x = worldPoint.x;
	world.y = worldPoint.y;
	world.z = worldPoint.z;

	Ogre::Vector3 screenPoint = mCamera_->getProjectionMatrix() * mCamera_->getViewMatrix() * world;

	Vector3 result;
	result.x = (screenPoint.x * 0.5 + 0.5);
	result.y = (-screenPoint.y * 0.5 + 0.5);
	result.z = screenPoint.z * 0.5 + 0.5;

	return result;

}

Vector3 CameraComponent::worldToScreenPixel(const Vector3& worldPoint)
{
	Ogre::Vector3 world;
	world.x = worldPoint.x;
	world.y = worldPoint.y;
	world.z = worldPoint.z;


	Ogre::Vector3 screenPoint = mCamera_->getProjectionMatrix() * mCamera_->getViewMatrix() * world;
	Ogre::Viewport* viewport = mCamera_->getViewport();

	Vector3 result;
	result.x = (screenPoint.x * 0.5 + 0.5) * viewport->getActualWidth();
	result.y = (-screenPoint.y * 0.5 + 0.5) * viewport->getActualHeight();
	result.z = screenPoint.z * 0.5 + 0.5;

	return result;
}

CameraComponent* createCamera(Entity* ent, std::string name, bool isMainCam){
	return new CameraComponent(ent,name,isMainCam);
}

void CameraComponent::setViewportDimensions(float left, float top, float width, float height)
{
	mCamera_->setViewport(left, top, width, height);
}

void CameraComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateCamera", createCamera).
		deriveClass<CameraComponent, AegisComponent>("Camera").
		addProperty("direction", &CameraComponent::getDirection, &CameraComponent::setDirection).
		addProperty("orientation", &CameraComponent::getOrientation, &CameraComponent::setOrientation).
		endClass().
		endNamespace().
		endNamespace();
}

void CameraComponent::setClipDistances(double near, double far)
{
}
