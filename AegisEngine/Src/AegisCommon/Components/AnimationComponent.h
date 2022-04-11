#pragma once
#include "AegisComponent.h"
#include "../Utils/Animation.h"
#include "../Interfaces/ILuaObject.h"

class Transform;

class AnimationComponent : public AegisComponent {
private:
	Animation animation;
	Transform* entTransform;

public:
	AnimationComponent(Entity* _ent, LuaRef args);
	void ReadKeyframes(LuaRef frames);
	void addFrames(const std::vector<keyFrame>& kf);
	virtual void init() {};
	virtual void update(float dt);
	static void ConvertToLua(lua_State* state);
};