#include "Sequence.h"
#include "../../BTUtils/AIAgent.h"
Sequence::Sequence():Composite()
{
	mIndex_ = 0;
}

Sequence::~Sequence()
{
    removeAllChildren();
}

BTNodeStatus Sequence::OnExecute(AIAgent agent)
{
    BTNodeStatus stat = BTNodeStatus::Success;
    bool exit = false;  // Exit condition of the sequence

    while (!exit &&mIndex_ < mChildren_.size())
    {
        //stat = mChildren_[mIndex_].Run(agent);
        exit = (stat != BTNodeStatus::Success);
       mIndex_++;
    }
    return stat;
}
