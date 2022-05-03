#include "Decorator.h"

Decorator::Decorator():
	BTNode()
{
}

Decorator::~Decorator()
{
	delete mChild_;
}

void Decorator::OnEnter(AIAgent agent)
{
	if (mChild_ != nullptr) {
		mChild_->OnEnter(agent);
	}
}

void Decorator::OnStart(AIAgent agent)
{
	if (mChild_ != nullptr) {
		mChild_->OnStart(agent);
	}
}

BTNodeStatus Decorator::OnExecute(AIAgent agent)
{
	return BTNodeStatus::None;
}
