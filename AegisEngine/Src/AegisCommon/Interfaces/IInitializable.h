#pragma once
#ifndef IINITIALIZABLE_H 
#define IINITIALIZABLE_H 

#include "../../checkML.h" //BASURA

class IInitializable
{
public:
	virtual bool Init() = 0;
};
#endif //