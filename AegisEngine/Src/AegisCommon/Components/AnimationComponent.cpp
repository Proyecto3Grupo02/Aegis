#include "AnimationComponent.h"
#include "../Entity/Entity.h"
#include "Transform.h"

AnimationComponent::AnimationComponent(Entity* _ent, Ogre::SceneManager* sceneMng)
{
	entTransform = _ent->GetTransform();
}

void AnimationComponent::addFrames(const std::vector<keyFrame>& frames) { //en el caso de pasar el vector entero
	keyFrame* kf;
	for (int i = 0; i < animation.numKeyFrames; i++) {
		kf->pos = frames[i].pos;
		kf->degrees = frames[i].degrees;
		kf->scale = frames[i].scale;
	}
}

void AnimationComponent::setLoop(bool isLoop) {
	loop = isLoop;
}

// Solo reinicia la animación si el estado cambia
void AnimationComponent::setEnabled(bool isEnabled) {
	if (!isActive && isEnabled)
	{
		animation.tiempoUltimoFrame = 0;
		animation.frameActual = 0;
	}
	else if (isActive && !isEnabled)
	{
		animation.tiempoUltimoFrame = 0;
		animation.frameActual = 0;
	}
	isActive = isEnabled;
}

void AnimationComponent::update(float dt)
{
	if (!isActive) return;

	if (dt - animation.tiempoUltimoFrame > animation.durFrame)
	{
		if (animation.frameActual < animation.numKeyFrames - 1)
			animation.frameActual++;
		else if (loop) animation.frameActual = 0;
		animation.tiempoUltimoFrame = dt;
	}

	// porcentaje de progreso de frame A a frame B
	float percentage = dt / (animation.tiempoUltimoFrame + animation.durFrame);

	Vector3 interpolatedPos = MathUtils::Lerp(animation.frames[animation.frameActual].pos, animation.frames[(animation.frameActual + 1)].pos, percentage);
	Vector3 interpolatedRot = MathUtils::Lerp(animation.frames[animation.frameActual].degrees, animation.frames[(animation.frameActual + 1)].degrees, percentage);
	Vector3 interpolatedScale = MathUtils::Lerp(animation.frames[animation.frameActual].scale, animation.frames[(animation.frameActual + 1)].scale, percentage);

	entTransform->SetPosition(interpolatedPos);
	entTransform->SetRotationEuler(interpolatedRot);
	entTransform->SetScale(interpolatedScale);
}