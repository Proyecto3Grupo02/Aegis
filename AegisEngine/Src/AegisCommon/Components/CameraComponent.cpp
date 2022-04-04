#include "CameraComponent.h"

CameraComponent::CameraComponent(Entity* ent): 
	AegisComponent("Camera", ent)
{
}

CameraComponent::~CameraComponent()
{
	delete mCamera_;
}

void CameraComponent::lookAt(const Vector3& dir)
{
}

Vector3 CameraComponent::getDirection() const
{
	return mDirection_;
}

Quaternion CameraComponent::getOrientation() const
{
	return mOrientation_;
}

void CameraComponent::setDirection(Vector3 dir)
{
}

void CameraComponent::setOrientation(const Quaternion& orientation)
{
}

Vector3 CameraComponent::worldToScreen(const Vector3& worldPoint)
{
	return Vector3();
}

Vector3 CameraComponent::worldToScreenPixel(const Vector3& worldPoint)
{
	return Vector3();
}
CameraComponent* createCamera(Entity* ent) {
	return new CameraComponent(ent);
}

void CameraComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateCamera", createCamera).
		deriveClass<CameraComponent, AegisComponent>("Camera").
		endClass().
		endNamespace().
		endNamespace();
}

void CameraComponent::setClipDistances(double, double)
{
}
