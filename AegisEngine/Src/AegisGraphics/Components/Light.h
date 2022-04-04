#pragma once
#include <OgreLight.h>
enum LightType{NONE, DIRLIGHT, POINTLIGHT, SPOTLIGHT};
class AegisLight {
public:
	AegisLight(Ogre::SceneNode* node,Ogre::SceneManager* sceneMng): 
		mngr_(sceneMng) {
		mType = LightType::NONE;
		initLight(node);
	}
	~AegisLight() {
		mNode_->detachObject(mLight_);
	}

	void setDirLight() {
		mType = LightType::DIRLIGHT;
		mLight_->setType(Ogre::Light::LT_DIRECTIONAL);
	}

	void setPointLight() {

		mType = LightType::POINTLIGHT;
		mLight_->setType(Ogre::Light::LT_POINT);
	}
	
	void setSpotLight() {

		mType = LightType::SPOTLIGHT;
		mLight_->setType(Ogre::Light::LT_SPOTLIGHT);
	}

	void setLightOn() {
		mNode_->setVisible(true);
	}
	void initLight(Ogre::SceneNode* node) {
		mNode_ = node;
		mLight_ = mngr_->createLight();
		mNode_->attachObject(mLight_);
	}
	void setLightOff() {
		mNode_->setVisible(false);
	}

	void setLightColor(float r, float g, float b) {
		mLight_->setDiffuseColour(r, g, b);
	}
	void setSpecularColor(float r, float g, float b) {
		mLight_->setSpecularColour(r, g, b);
	}
	
	bool isVisible() const {
		return mLight_->isVisible();
	}
	
	bool isSpotLight() const {
		return mType == LightType::SPOTLIGHT;
	}
	bool isDirLight() const {
		return mType == LightType::DIRLIGHT;
	}
	bool isPointLight() const {
		return mType == LightType::POINTLIGHT;
	}

private:
	LightType mType;
	Ogre::SceneNode* mNode_;
	Ogre::Light* mLight_;
	Ogre::SceneManager* mngr_;
};