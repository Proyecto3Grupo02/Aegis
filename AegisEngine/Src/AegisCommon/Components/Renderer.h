#pragma once
#ifndef  RENDERER_H 
#define RENDERER_H

#include "../Managers/ComponentManager.h" //Da error en el cpp
#include "AegisComponent.h" //Da error en el cpp
#include "../Interfaces/ILuaObject.h"

class OgreWrapper;
class Transform;
class AegisComponent;

class Renderer : public AegisComponent, public ILuaObject {
public:
	Renderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir = true):
		AegisComponent()
	{
		isVisible = ir;
		ComponentManager::getInstance()->RegisterComponent<Renderer>("Renderer");
		constructoraRenderer(_ent, meshName, sceneMng, ir);
	}

	Renderer(Entity* _ent, std::string meshName);

	~Renderer() {};
	void update(float dt) override {}
	void render();
	virtual void init(){};
	void setRendering(bool iR);
	bool getRendering() const;
	Ogre::Entity* getMesh() { return mesh; };

	static void ConvertToLua(lua_State* state);
protected:
	void constructoraRenderer(Entity* _ent, std::string meshName, Ogre::SceneManager* sceneMng, bool ir);

	Ogre::SceneNode* node;
	Transform* transform;
	Ogre::Entity* mesh;
	bool isVisible;
};


#endif //RENDERER_H