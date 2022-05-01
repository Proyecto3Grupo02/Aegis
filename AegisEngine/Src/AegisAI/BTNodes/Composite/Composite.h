#pragma once
#ifndef _COMPOSITE
#define _COMPOSITE
#include "../BTNode.h"
#include <list>
class Composite: public BTNode {
public:
	Composite();
	~Composite();

	void addChild(int index, BTNode* child);
	void addChild(BTNode* child);

	void removeChild(int index);
	void removeChild(BTNode* child);

	void removeAllChildren();

	void OnEnter(AIAgent agent) override;
	void OnStart(AIAgent agent) override;


	virtual BTNodeStatus OnExecute (AIAgent agent) override;


protected:
	std::list<BTNode*> mChildren_;
};

#endif // !_COMPOSITE


