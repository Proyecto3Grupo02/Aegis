#include "SoundListener.h"

SoundListener::SoundListener() 
{
    
	SoundSystem* soundSystem = SoundSystem::getInstance();
    
    quat = Vector4(0);
    pos = Vector3(0);
    soundSystem->createListener(&pos, &quat);

}