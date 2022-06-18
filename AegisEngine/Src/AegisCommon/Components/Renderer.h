#pragma once
#ifndef  RENDERER_H 
#define RENDERER_H


#include "AegisComponent.h" //Da error en el cpp
#include "ILuaObject.h"

class OgreWrapper;
class Transform;
class AegisComponent;

class Renderer : public AegisComponent, public ILuaObject {
public:
	Renderer(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir = true);
	Renderer(Entity* _ent, std::string meshName, std::string matName);
	Renderer();

	~Renderer() {};
	void update(float dt) override {}
	void render() override;
	virtual void init() override {};
	void setRendering(bool iR);
	bool getRendering() const;

	Ogre::Entity* getMesh() { return mesh; };

	static void ConvertToLua(lua_State* state);
protected:
	void constructoraRenderer(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir);
	void constructoraRendererLua(Entity* _ent, std::string meshName, std::string matName);

	Ogre::SceneNode* node;
	Transform* transform;
	Ogre::Entity* mesh;
	bool isVisible;
};


#endif //RENDERER_H