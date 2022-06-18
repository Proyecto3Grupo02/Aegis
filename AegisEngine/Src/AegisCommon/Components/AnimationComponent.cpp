#include "AnimationComponent.h"
#include "Entity.h"
#include "Transform.h"

AnimationComponent::AnimationComponent(Entity* _ent, LuaRef args) : AegisComponent("Animation", _ent)
{
	this->data = args;
	entTransform = _ent->GetTransform();
	animation.loop = LuaMngr()->ParseBool(args["loop"]);

	LuaRef keyframes = args["keyframes"];
	if (!keyframes.isNil())
		ReadKeyframes(keyframes);

	SetDataAsInnerType(this);
}

//Esto hay que moverlo a otro sitio, pero en luaref causaria dependencias con aegiscommons asi que no se
Vector3 ParseVector3(LuaRef ref, int defaultValue)
{
	if (ref.isNil())
		return Vector3(defaultValue, defaultValue, defaultValue);

	float x = LuaMngr()->ParseFloat(ref["x"], defaultValue);
	float y = LuaMngr()->ParseFloat(ref["y"], defaultValue);
	float z = LuaMngr()->ParseFloat(ref["z"], defaultValue);

	return Vector3(x, y, z);
}

void AnimationComponent::ReadKeyframes(LuaRef frames)
{
	int numFrames = frames.length();
	animation.numKeyFrames = numFrames;

	//If some keyframe doesn't define a property, it will take the value of the keyframe before. If
	//the first keyframe doesn't define a property, it will take the default value
	keyFrame currentFrame;
	for (int i = 1; i < numFrames + 1; i++)
	{
		LuaRef frame = frames[i];
		if (!frame["rotation"].isNil())
			currentFrame.degrees = ParseVector3(frame["rotation"], 1);
		if (!frame["position"].isNil())
			currentFrame.pos = ParseVector3(frame["position"], 1);
		if (!frame["scale"].isNil())
			currentFrame.scale = ParseVector3(frame["scale"], 1);
		if (!frame["time"].isNil())
			currentFrame.time = LuaMngr()->ParseFloat(frame["time"]);
		else
			std::cerr << "No time data given for this keyFrame, this can lead to undefined behaviour\n";

		animation.addKeyframe(currentFrame);
	}
}

void AnimationComponent::update(float dt)
{
	if (animation.finished) return;

	animation.addTime(dt);
	
	entTransform->SetPosition(animation.GetInterpolatedPos());
	entTransform->SetRotationEuler(animation.GetInterpolatedEulerAngles());
	entTransform->SetScale(animation.GetInterpolatedScale());
}

AnimationComponent* CreateAnimation(Entity* _ent, LuaRef args)
{
	return new AnimationComponent(_ent, args);
}

void AnimationComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateAnimation", CreateAnimation).
		deriveClass<AnimationComponent, AegisComponent>("Animation").
		endClass().
		endNamespace().
		endNamespace();
}
