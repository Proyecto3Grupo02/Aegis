#include "AnimationComponent.h"
#include "../Entity/Entity.h"

AnimationComponent::AnimationComponent(Entity* _ent, Ogre::SceneManager* sceneMng,std::string nombre, int dur):
	duracion(dur), enabled(false), loop(false)
{
	Ogre::Animation* animation = sceneMng->createAnimation(nombre, duracion);
	nodeTrack = animation->createNodeTrack(0);
	nodeTrack ->setAssociatedNode(_ent->getNode());
	_ent->getNode()->setInitialState();
	durFrame = duracion / numKeyFrames;
}


Ogre::NodeAnimationTrack* AnimationComponent::getTrack() {
	return nodeTrack;
}

void AnimationComponent::addFrames(const std::vector<keyFrame>& frames) { //en el caso de pasar el vector entero
	Ogre::TransformKeyFrame* kf;
	for (int i = 0; i < numKeyFrames; i++) {
		kf = nodeTrack->createNodeKeyFrame(durFrame * i); //0 estado inicial		
		kf->setTranslate(frames[i].pos);
		kf->setRotation(Ogre::Quaternion(Ogre::Degree(frames[i].degrees), frames[i].boolRot));
		kf->setScale(frames[i].scale);		
	}
}

void AnimationComponent::setLoop(bool isLoop) {
	loop = isLoop;
}

void AnimationComponent::setEnabled(bool isEnabled) {
	enabled = isEnabled;
}