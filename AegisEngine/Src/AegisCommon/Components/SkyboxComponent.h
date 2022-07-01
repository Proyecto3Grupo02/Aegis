#pragma once
#ifndef  SKYBOX_H 
#define SKYBOX_H

#include "AegisComponent.h" 
#include "ILuaObject.h"

class OgreWrapper;
class TransformComponent;

class SkyboxComponent : public AegisComponent, public ILuaObject {
public:
	// Constructoras
	SkyboxComponent(Entity* _ent, std::string matName, bool ir = true);
	SkyboxComponent(Entity* _ent, std::string matName);
	SkyboxComponent();
	~SkyboxComponent() { 
	};
	void setRendering(bool iR) {	isVisible = iR;	};
	bool getRendering() const {		return isVisible;  };

	static void ConvertToLua(lua_State* state);

protected:
	void constructoraSkybox(Entity* _ent, std::string matName, bool ir);
	void constructoraSkyboxLua(Entity* _ent, std::string matName);

	bool isVisible = true;
};

#endif //SKYBOX_H