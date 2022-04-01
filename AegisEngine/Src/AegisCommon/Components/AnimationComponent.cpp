#include "AnimationComponent.h"
AnimationComponent::AnimationComponent(Ogre::SceneManager* sceneMng,std::string nombre, int duracion)
{
	//Ogre::Animation* animation = createAnimation(nombre, duracion);
}
Ogre::NodeAnimationTrack* AnimationComponent::getTrack()
{
	return nodeTrack;
}
void AnimationComponent::addKeyFrame(keyFrame kf)
{
	frames.push_back(kf);
}
void AnimationComponent::setLoop(bool isLoop)
{
	loop = isLoop;
}
void AnimationComponent::setEnabled(bool isEnabled)
{
	enabled = isEnabled;
}