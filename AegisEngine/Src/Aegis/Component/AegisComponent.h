#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT
#include "Component.h"
class Entity;
class AegisComponent : public Component {
public: 
	AegisComponent() : Component(){}
	virtual ~AegisComponent(){}
};
#endif