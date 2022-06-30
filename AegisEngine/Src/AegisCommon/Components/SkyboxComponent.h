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
	SkyboxComponent(Entity* _ent, std::string matName, Ogre::SceneManager* sceneMng, bool ir = true);
	SkyboxComponent(Entity* _ent, std::string matName);
	SkyboxComponent();
	~SkyboxComponent() { 
		delete mesh; 
		mesh = nullptr;
	};

	void update(float dt) override {}
	void render() override {}
	virtual void init() override {};
	void setRendering(bool iR) {	isVisible = iR;	node->setVisible(iR);	};
	bool getRendering() const {		return isVisible;  };

	Ogre::Entity* getMesh() { return entity; };

	static void ConvertToLua(lua_State* state);

protected:
	void constructoraSkybox(Entity* _ent, std::string matName, Ogre::SceneManager* sceneMng, bool ir);
	void constructoraSkyboxLua(Entity* _ent, std::string matName);

	Ogre::SceneNode* node = nullptr;
	TransformComponent* transform = nullptr;
	Ogre::Plane* mesh;
	Ogre::Entity* entity = nullptr;
	bool isVisible = true;
};


#endif //SKYBOX_H