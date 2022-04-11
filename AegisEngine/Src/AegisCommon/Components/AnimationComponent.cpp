#include "AnimationComponent.h"
#include "../Entity/Entity.h"
#include "Transform.h"

AnimationComponent::AnimationComponent(Entity* _ent, LuaRef args) : AegisComponent("Animation", _ent)
{
	entTransform = _ent->GetTransform();
	animation.loop = LuaMngr()->ParseBool(args["loop"]);

	LuaRef keyframes = args["keyframes"];
	if (!keyframes.isNil())
		ReadKeyframes(keyframes);
}

void AnimationComponent::ReadKeyframes(LuaRef frames)
{
}

void AnimationComponent::addFrames(const std::vector<keyFrame>& frames) { //en el caso de pasar el vector entero
	keyFrame* kf;
	for (int i = 0; i < animation.numKeyFrames; i++) {
		kf->pos = frames[i].pos;
		kf->degrees = frames[i].degrees;
		kf->scale = frames[i].scale;
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
