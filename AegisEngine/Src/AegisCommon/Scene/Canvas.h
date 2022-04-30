#pragma once 


#include <list>
#include "../Interfaces/ILuaObject.h"
#include "../Interfaces/IInitializable.h"

struct UIElement;
class OgreWrapper;

class Canvas: public ILuaObject, public IInitializable
{
private:
	OgreWrapper* ogreWrapper;
   std::list<UIElement*>* mElems_;
   std::list<std::list<UIElement*>::iterator> elemsToDelete;
public:
    Canvas(OgreWrapper* wrap);
    ~Canvas();

    void render();
    void update();

    void OnClickDown();
    void OnClickUp();


    void OnMouseOver();
    void OnMouseExit();

};
