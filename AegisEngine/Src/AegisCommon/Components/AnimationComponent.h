#pragma once

#ifndef ANIMATION_COMPONENT
#define ANIMATION_COMPONENT

#include "AegisComponent.h"
#include "ILuaObject.h"
#include "Animation.h"

class TransformComponent;

class AnimationComponent : public AegisComponent, public ILuaObject {
private:
	Animation animation;
	TransformComponent* entTransform = nullptr;

public:
	AnimationComponent(Entity* _ent, LuaRef args);
	void readKeyframes(LuaRef frames);
	virtual void init() {};
	virtual void update(float dt);
	static void ConvertToLua(lua_State* state);
};
# endif