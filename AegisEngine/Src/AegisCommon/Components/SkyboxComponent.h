#pragma once
#ifndef  RENDERER_H 
#define RENDERER_H

#include "AegisComponent.h" 
#include "ILuaObject.h"

class OgreWrapper;
class TransformComponent;
class AegisComponent;

class SkyboxComponent : public AegisComponent, public ILuaObject {
public:
	// Constructoras
	SkyboxComponent(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir = true);
	SkyboxComponent(Entity* _ent, std::string meshName, std::string matName);
	SkyboxComponent();
	~SkyboxComponent() {};

	void update(float dt) override {}
	void render() override {}
	virtual void init() override {};
	void setRendering(bool iR) {	isVisible = iR;	node->setVisible(iR);	};
	bool getRendering() const {		return isVisible;  };

	Ogre::Entity* getMesh() { return mesh; };

	static void ConvertToLua(lua_State* state);

protected:
	void constructoraSkybox(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir);
	void constructoraSkyboxLua(Entity* _ent, std::string meshName, std::string matName);

	Ogre::SceneNode* node = nullptr;
	TransformComponent* transform = nullptr;
	Ogre::Entity* mesh = nullptr;
	bool isVisible = true;
};


#endif //RENDERER_H