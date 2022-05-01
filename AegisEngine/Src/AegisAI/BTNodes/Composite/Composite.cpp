#include "Composite.h"
#include "../../BTUtils/AIAgent.h"
Composite::Composite():
	BTNode()
{
}

Composite::~Composite()
{
}

void Composite::addChild(int index, BTNode* child)
{
}

void Composite::addChild(BTNode* child)
{
	mChildren_.push_back(child);
}

void Composite::removeChild(int index)
{
}

void Composite::removeChild(BTNode* child)
{
	mChildren_.remove(child);

}

void Composite::removeAllChildren()
{
	mChildren_.clear();
}

void Composite::OnEnter(AIAgent agent)
{
	for (auto* c : mChildren_) {
		c->OnEnter(agent);
	}
}

void Composite::OnStart(AIAgent agent)
{
	for (auto* c : mChildren_) {
		c->OnStart(agent);
	}
}

BTNodeStatus Composite::OnExecute(AIAgent agent)
{
	return BTNodeStatus::None;
}
