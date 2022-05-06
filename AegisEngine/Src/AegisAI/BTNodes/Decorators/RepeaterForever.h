#pragma once

#include "Decorator.h"
class RepeaterForever: public Decorator
{
private:

public:
    RepeaterForever(/* args */);
    ~RepeaterForever();
    BTNodeStatus OnExecute(AIAgent agent) override;
};

