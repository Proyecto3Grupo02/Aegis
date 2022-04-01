#pragma once
#include "AegisComponent.h"
#include <OgreAnimation.h>
#include <OgreAnimationState.h>
#include <OgreKeyFrame.h>
#include <OgreAnimationTrack.h>
#include <Vector3.h>

class Transform;
class OgreWrapper;

struct keyFrame {
	Ogre::Vector3 pos, boolRot, scale;
	Ogre::Degree degrees;
};

class AnimationComponent : public AegisComponent {
private: 
	Ogre::Animation* animation;
	Ogre::NodeAnimationTrack* nodeTrack;
	Transform* entTransform;
	int numKeyFrames;
	double duracion, durFrame;
	std::vector<keyFrame> frames;
	bool loop, enabled;

public:
	AnimationComponent(Entity* _ent, Ogre::SceneManager* sceneMng, std::string nombre, int duracion);
	~AnimationComponent();
	Ogre::NodeAnimationTrack* getTrack();
	void addFrames(const std::vector<keyFrame>& kf);
	void setEnabled(bool enabled);
	void setLoop(bool isLoop);
	virtual void init();
	virtual void update(float dt);
	
};