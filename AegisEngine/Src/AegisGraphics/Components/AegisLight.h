#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <OgreLight.h>

enum LightType { NONE, DIRLIGHT, POINTLIGHT, SPOTLIGHT };

class AegisLight {
public:
	AegisLight(Ogre::SceneNode* node, Ogre::SceneManager* sceneMng) :
		mngr_(sceneMng) {
		mType = LightType::NONE;
		initLight(node);
		setPointLight();
	}
	~AegisLight() {
		mngr_->destroyLight(mLight_);
	}

	static std::string LightTypeToString(LightType mType)
	{
		std::string type;
		switch (mType)
		{
		case LightType::DIRLIGHT:
			type = "DirLight";
			break;
		case LightType::POINTLIGHT:
			type = "PointLight";
			break;
		case LightType::SPOTLIGHT:
			type = "SpotLight";
			break;
		default:
			type = "None";
			break;
		}
		return type;
	}

	void setLightType(std::string lightType)
	{
		if (lightType == "DirLight")
			setDirLight();
		else if (lightType == "PointLight")
			setPointLight();
		else if (lightType == "SpotLight")
			setSpotLight();
	}

	void setDirection(float x, float y, float z)
	{
		mNode_->setDirection(Ogre::Vector3(x, y, z));
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
		return mType == LightTypeToString(LightType::SPOTLIGHT);
	}
	bool isDirLight() const {
		return mType == LightTypeToString(LightType::DIRLIGHT);
	}
	bool isPointLight() const {
		return mType == LightTypeToString(LightType::POINTLIGHT);
	}

private:
	std::string mType;
	Ogre::SceneNode* mNode_ = nullptr;
	Ogre::Light* mLight_ = nullptr;
	Ogre::SceneManager* mngr_ = nullptr;
};

# endif