#pragma once

#ifndef BUTTON_COMPONENT_COMPONENT_H
#define BUTTON_COMPONENT_COMPONENT_H

#include "AegisComponent.h"
#include "ILuaObject.h"
#include "../AegisUI/Button.h"
#include <string>

class Entity;
//static int id = 0;

class ButtonComponent : public AegisComponent, public ILuaObject
{
public:
	ButtonComponent(Entity* ent, const std::string& name, int order, std::string material, float x, float y, float w, float h);
	virtual ~ButtonComponent();

	virtual void init() override {};
	virtual void update(float deltaTime) override;
	virtual void lateUpdate(float deltaTime) override {};
	virtual void fixedUpdate() override {};


	//GETS----------
	bool isActive() const;

	//LUA------------
	static void ConvertToLua(lua_State* state);
	bool wasClicked();
private:
	Button* boton = nullptr;

};

#endif