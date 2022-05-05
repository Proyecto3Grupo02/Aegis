#pragma once 


#include <list>
#include "../Interfaces/ILuaObject.h"
#include "../Interfaces/IInitializable.h"

class UIElement;
class OgreWrapper;

class Canvas : public ILuaObject
{
private:
	OgreWrapper* ogreWrapper;
	std::list<UIElement*>* mElems_;
	std::list<std::list<UIElement*>::iterator> elemsToDelete;
public:
	Canvas(OgreWrapper* wrap);
	~Canvas();


	void render();

	void OnClickDown();
	void OnClickUp();

	void OnMouseOver();
	void OnMouseExit();

	void addUIElement(UIElement* elem);

	static void ConvertToLua(lua_State* state);

};
