#include "SoundEmitter.h"

#include "../AegisCommon/Managers/DebugManager.h"
#include "../AegisCommon/Utils/Vector3.h"
#include <fmod.hpp>

SoundListener::SoundListener() 
{
    
    SoundSystem* soundSystem = SoundSystem::GetInstance();
    
    soundSystem->createListener(&gameObject->transform->getPosition(), &gameObject->transform->getQuaternion());
}

SoundListener::~SoundListener()
{

}