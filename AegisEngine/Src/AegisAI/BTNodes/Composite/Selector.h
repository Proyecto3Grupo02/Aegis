#pragma once 

#include "Composite.h"
class Selector: 
	public Composite {
public:
	Selector();
	~Selector();

	BTNodeStatus OnExecute(AIAgent agent) override;
private:
	int mIndex_;
};