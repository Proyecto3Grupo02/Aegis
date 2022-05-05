#pragma once
#ifndef _BTNODE
#define _BTNODE

#include "../BTUtils/BTNodeStatus.h"
#include "../BTUtils/AIAgent.h"

class BTNode
{
protected:
    BTNodeStatus mStatus_;
public:
    BTNode(/* args */);
    virtual ~BTNode()=default;

    // All behaviour nodes overload this methods 
    virtual void OnStart(AIAgent agent)=0;
    virtual void OnReset()=0;
    virtual void OnEnter(AIAgent agent) = 0;
    virtual void OnExit(AIAgent agent) = 0;
    virtual BTNodeStatus OnExecute(AIAgent agent) = 0;

    virtual BTNodeStatus Run(AIAgent agent) =0;

    BTNodeStatus getStatus() const { return mStatus_; }

};

#endif