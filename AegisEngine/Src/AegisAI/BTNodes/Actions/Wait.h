#pragma once

#ifndef _WAIT
#define _WAIT

#include <OgreTimer.h>
#include "../BTNode.h"
#include "Action.h"

class AIAgent;

// Wait is a node that waits for x ms and then executes a node
class Wait : public Action
{

private:
    Ogre::Real mDuration;
    Ogre::Real mStartTime;

public:
    Wait(Ogre::Real waitTime){ mDuration = waitTime; };
    ~Wait() = default;

    virtual BTNodeStatus Run(AIAgent agent);
    virtual void OnEnter(AIAgent agent){ 
        mStartTime = Ogre::Timer::getMiliseconds();
    };

    // Failure is not an option; You either running or succeding
    virtual BTNodeStatus OnExecute(AIAgent agent){
        Ogre::Real duration = 0;
        if(Ogre::Timer::getMiliseconds() < mStartTime + mDuration)
            return BTNodeStatus::Running;
        else
            return BTNodeStatus::Success;
    };
};

#endif