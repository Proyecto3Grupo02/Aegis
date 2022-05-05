#pragma once

#include "Composite.h"
class Sequence :
	public Composite {
public:
	Sequence();
	~Sequence();
	BTNodeStatus OnExecute(AIAgent agent) override;
private:
	int mIndex_;
};