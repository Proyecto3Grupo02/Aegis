#pragma once 
#ifndef _DECORATOR_
#include "../BTNode.h"

class Decorator: public BTNode
{
protected:
    BTNode* mChild_;
public:
    Decorator(/* args */);
    ~Decorator();

    void OnEnter(AIAgent agent) override;
	void OnStart(AIAgent agent) override;

    BTNodeStatus OnExecute(AIAgent agent) override ;


    BTNode* getChild() const{return mChild_;}
    void setChild(BTNode* child){mChild_=child;}

};
#endif