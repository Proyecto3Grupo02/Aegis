#pragma once
#include "AegisComponent.h"
#include <Vector3.h>
#include <MathUtils.h>

class Transform;
class OgreWrapper;

struct keyFrame {
	Vector3 pos, scale;
	Vector3 degrees;
};

struct Animation {
	int numKeyFrames = 0;
	double durFrame = 0;
	int frameActual = 0;
	std::vector<keyFrame> frames;
	float tiempoUltimoFrame = 0;
};

class AnimationComponent : public AegisComponent {
private: 
	Animation animation;
	Transform* entTransform;
	bool isActive = false;
	bool loop = false;

public:
	AnimationComponent(Entity* _ent, Ogre::SceneManager* sceneMng);
	~AnimationComponent();
	void addFrames(const std::vector<keyFrame>& kf);
	void setEnabled(bool enabled);
	void setLoop(bool isLoop);
	virtual void init();
	virtual void update(float dt);
	
};