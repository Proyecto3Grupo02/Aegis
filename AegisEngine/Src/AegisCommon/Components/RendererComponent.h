#pragma once
#ifndef  RENDERER_H 
#define RENDERER_H

#include "AegisComponent.h" 
#include "ILuaObject.h"

class OgreWrapper;
class TransformComponent;
class AegisComponent;

class RendererComponent : public AegisComponent, public ILuaObject {
public:
	RendererComponent(Entity* _ent, std::string meshName, std::string matName, Ogre::SceneManager* sceneMng, bool ir = true);
	RendererComponent(Entity* _ent, std::string meshName, std::string matName);
	RendererComponent();

	~RendererComponent() {};
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

	Ogre::SceneNode* node = nullptr;
	TransformComponent* transform = nullptr;
	Ogre::Entity* mesh = nullptr;
	bool isVisible = true;
};


#endif //RENDERER_H