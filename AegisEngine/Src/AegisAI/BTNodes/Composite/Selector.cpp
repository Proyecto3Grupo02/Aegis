#include "Selector.h"
Selector::Selector() : Composite()
{
    mIndex_ = 0;
}

Selector::~Selector()
{
    removeAllChildren();
}

BTNodeStatus Selector::OnExecute(AIAgent agent)
{
    BTNodeStatus stat = BTNodeStatus::Success;
    BTNodeStatus result = BTNodeStatus::Success;

    while (mIndex_< mChildren_.size())
    {
        //stat = mChildren_[mIndex_].Run(agent);
        if (stat == BTNodeStatus::Success)
        {
            result = stat;
        }
        mIndex_++;
    }
    return result;
}
