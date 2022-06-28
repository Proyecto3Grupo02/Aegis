#include "SoundListenerComponent.h"
#include "SoundSystem.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "MathUtils.h"

SoundListenerComponent::SoundListenerComponent(Entity* ent) : AegisComponent("SoundListener", ent), transform(ent->getTransform())
{
	SoundSystem::getInstance()->createListener(transform->getPosition(), MathUtils::OgreQuatToVec4(transform->getRotation()));
}

SoundListenerComponent::~SoundListenerComponent()
{
}

void SoundListenerComponent::update(float deltaTime)
{
	SoundSystem::getInstance()->updateListener(transform->getPosition(), MathUtils::OgreQuatToVec4(transform->getRotation()));
}

inline SoundListenerComponent* createSoundListener(Entity* ent) {
	return new SoundListenerComponent(ent);
}

void SoundListenerComponent::ConvertToLua(lua_State* state)
{
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateSoundListener", createSoundListener).
		deriveClass<SoundListenerComponent, AegisComponent>("SoundEmitter").
		endClass().
		endNamespace().
		endNamespace();
}
