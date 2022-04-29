#pragma once 

#include "../Interfaces/ILuaObject.h"

class RectTransform;
class Scene;
struct Vector2;
struct UIElement: 
    public ILuaObject
{
private:
    std::string mName_; //name of the entity, works like a tag, useful to debug
    RectTransform* mTransform_;
    Scene* mScene_;

public:
    UIElement(Scene* scene, Vector2 pos);
    ~UIElement();

    inline std::string getName() const { return mName_; }
};

