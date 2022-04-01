#pragma once
#include "AegisComponent.h"
#include <OgreAnimation.h>
#include <OgreAnimationState.h>
#include <OgreKeyFrame.h>
#include <Vector3.h>

class Transform;
class OgreWrapper;

struct keyFrame {
	Vector3 pos, rot, scale;
};

class AnimationComponent : public AegisComponent {
private: 
	Ogre::Animation* animation;
	Ogre::NodeAnimationTrack* nodeTrack;
	Transform* entTransform;
	int numKeyFrames, durFrame;
	std::vector<keyFrame> frames;
	

public:
	AnimationComponent();
	~AnimationComponent();

	void setEnabled(bool enabled);
	void setLoop(bool isLoop);
	virtual void init();
	virtual void update(float dt);
	
};