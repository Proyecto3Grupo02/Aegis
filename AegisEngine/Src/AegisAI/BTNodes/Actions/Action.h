#pragma once
#include "../BTNode.h"
class AIAgent;
class Action: public BTNode
{
private:
    /* data */
public:
    Action(/* args */);
    ~Action() = default;

    virtual BTNodeStatus Run(AIAgent agent);
    

};

