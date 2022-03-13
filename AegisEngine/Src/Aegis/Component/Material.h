
#pragma once
#include "AegisComponent.h"

class Renderer;

class Material: public AegisComponent {
public: 
	Material();
	Material(std::string matName);
	virtual ~Material();

	virtual void init();

private:
	Renderer* mRenderer_;
	std::string mMaterialName_;
};