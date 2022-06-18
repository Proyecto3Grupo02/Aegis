#include "ButtonComponent.h"
#include "Entity.h"
#include <Scene.h>
#include "GameLoopData.h"
#include "MathUtils.h"

ButtonComponent::ButtonComponent(Entity* ent, const std::string& name, int order, std::string material, float x, float y, float w, float h)
	: AegisComponent("Button", ent) {

	boton = new Button(name, order, material, x, y, w, h);
	id++; //necesitamos que cada boton tenga un nombre distinto
	//mEntity_->getScene()->AddPhysicsEntity(this);
	SetDataAsInnerType(this);
}

ButtonComponent::~ButtonComponent() {
	delete boton;
	//mEntity_->getScene()->RemovePhysicsEntity(this->physicsEntityIt);
}

void ButtonComponent::update(float deltaTime) {
	boton->update();
}

//GETS----------

//LUA------------
bool ButtonComponent::isActive() const {
	return boton->getActive();
}

ButtonComponent* CreateButton(Entity* ent, LuaRef args) //Doesn't belong to this class
{//const std::string& name, int order, std::string material, float x, float y, float w, float h
	//std::string bodyName = ent->getName();
	std::string name = LuaMngr()->ParseString(args["name"], "Boton"+id); //PETA SI HAY MAS DE 1 CON EL MISMO NOMBRE ==> CUIDADO
	int order = LuaMngr()->ParseFloat(args["order"], 1);
	std::string material = LuaMngr()->ParseString(args["material"], "grass");
	float x = LuaMngr()->ParseFloat(args["x"], 1);
	float y = LuaMngr()->ParseFloat(args["y"], 1);
	float w = LuaMngr()->ParseFloat(args["width"], 1);
	float h = LuaMngr()->ParseFloat(args["height"], 1);

	return new ButtonComponent(ent, name, order, material, x, y, w, h);
}


bool ButtonComponent::wasClicked() {
	return boton->wasClicked();
}

void ButtonComponent::ConvertToLua(lua_State* state) {
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginNamespace("NativeComponents").
		addFunction("CreateButton", CreateButton).
		deriveClass<ButtonComponent, AegisComponent>("Button").
		//addProperty("position", &RigidbodyComponent::GetPosition, &RigidbodyComponent::SetPosition).		
		addFunction("wasClicked", &ButtonComponent::wasClicked).
		addProperty("isActive", &ButtonComponent::isActive).
		endClass().
		endNamespace().
		endNamespace();
}
