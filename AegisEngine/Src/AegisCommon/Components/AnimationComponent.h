#pragma once
#include "AegisComponent.h"
#include "../Interfaces/ILuaObject.h"
#include "../Utils/Animation.h"

class Transform;

class AnimationComponent : public AegisComponent, public ILuaObject {
private:
	Animation animation;
	Transform* entTransform;
public:
	AnimationComponent(Entity* _ent, LuaRef args);
	void ReadKeyframes(LuaRef frames);
	virtual void init() {};
	virtual void update(float dt);
	static void ConvertToLua(lua_State* state);
};