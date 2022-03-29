#include "DebugManager.h"
#include <iostream>
#include <OgreColourValue.h>

DebugManager::DebugManager(): 
	Singleton()
{

	//necesito el scene manager para debugear lineas
}

DebugManager::~DebugManager()
{
}

void DebugManager::Log(const std::string& msg) {
	std::cout<<"DEBUG: " << msg << std::endl;
}

void DebugManager::LogWarning(const std::string& msg) {
	std::cout <<"WARNING: " << msg << std::endl;
}
void DebugManager::LogError(const std::string& msg) {
	std::cout <<"ERROR: " << msg << std::endl;
}

void DebugManager::drawLine(Vector3 origin,  Vector3 end, Vector3 color) {	
	Ogre::Vector3 a = Ogre::Vector3(origin.GetX(), origin.GetY(), origin.GetZ());
	Ogre::Vector3 b = Ogre::Vector3(end.GetX(), end.GetY(), end.GetZ());
	
	Ogre::ColourValue c(color.GetX(), color.GetY(), color.GetZ());
	c.saturate();
	mLines_->position(a);
	mLines_->colour(c);
	mLines_->position(b);
	mLines_->colour(c);
}

bool DebugManager::Init() {
	mLines_ = new Ogre::ManualObject("lines");
	assert(mLines_);
	mLines_->setDynamic(true);

	return true;
}
