#pragma once

#ifndef _WAIT
#define _WAIT

#include "../BTNode.h"
#include "Action.h"

class AIAgent;

class Wait : public Action
{
private:
    float mDuration;
    float mStartTime;
public:
    Wait(/* args */){};
    ~Wait() = default;

    virtual BTNodeStatus Run(AIAgent agent);
    virtual void OnEnter(AIAgent agent){ mStartTime = Time.time; }

    virtual BTNodeStatus OnExecute(AIAgent agent){
        float duration = 0;
        if(Time.time < mStartTime + mDuration)
            return BTNodeStatus::Running;
        return BTNodeStatus::Success;
    };
};

#endif