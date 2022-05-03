#include "RepeaterForever.h"

RepeaterForever::RepeaterForever(): Decorator()
{
}

RepeaterForever::~RepeaterForever()
{
}

BTNodeStatus RepeaterForever::OnExecute(AIAgent agent)
{
	if (mChild_ != nullptr) {
		if (mChild_->getStatus() != BTNodeStatus::None||
			mChild_->getStatus() != BTNodeStatus::Running) {
			mChild_->OnReset();
		}
		mChild_->Run(agent);
	}
	return BTNodeStatus::Running;
}
