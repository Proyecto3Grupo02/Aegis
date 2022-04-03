#include "Light.h"
#include "../Entity/Entity.h"
Light::Light(): 
	AegisComponent(), mAmbient_(0,0,0), mDiffuse_(1,1,1), mSpecular_(0,0,0), mTr_(nullptr), mLight_(nullptr), mngr_(nullptr)
{
	SetDataAsInnerType(this);
	SetComponentName("Light");
}

Light::Light(Vector3 amb, Vector3 diff, Vector3 spec, Ogre::SceneManager* sceneMng):
	AegisComponent(), mAmbient_(amb), mDiffuse_(diff), mSpecular_(spec), mngr_(sceneMng), mTr_(nullptr), mLight_(nullptr)
{
	SetDataAsInnerType(this);
	SetComponentName("Light");
}

void Light::init()
{
	Ogre::SceneNode* mNode = getEntity()->getNode();
	mTr_= getEntity()->GetTransform();
	assert(mTr_ != nullptr);

	mLight_ = mngr_->createLight();
	mNode->attachObject(mLight_);
	renderLight();
}

void Light::renderLight()
{
	if (mAmbient_.x != 0.0 && mAmbient_.y != 0.0 && mAmbient_.z != 0.0) {
		Ogre::ColourValue c;
		c.r = mAmbient_.x;
		c.g = mAmbient_.y;
		c.b = mAmbient_.z;
		mngr_->setAmbientLight(c);
	}

	mLight_->setDiffuseColour(mDiffuse_.x, mDiffuse_.y, mDiffuse_.z);
	mLight_->setSpecularColour(mSpecular_.x, mSpecular_.y, mSpecular_.z);

}

void Light::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		deriveClass<Light, AegisComponent>("Light").
		addProperty("ambient", &Light::getAmbient, &Light::setAmbient).
		addProperty("diffuse", &Light::getDiffuse, &Light::setDiffuse).
		addProperty("specular", &Light::getSpecular, &Light::setSpecular).
		endClass().
		endNamespace().
		endNamespace();
}


Light::~Light()
{
}