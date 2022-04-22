#pragma once 

#include "../Utils/Vector2.h"
#include "AegisComponent.h"
#include "../Interfaces/ILuaObject.h"

class UITransform: public AegisComponent, public ILuaObject
{
public:
    UITransform(Entity* ent, Vector2 pos, Vector2 scale, float rotation);
    UITransform(Entity* ent, LuaRef* ref);

    ~UITransform();

    Vector2 getPosition() const;
    void setPosition(Vector2 pos);
    void setPosition(float x, float y);

    Vector2 getScale() const;
    void setScale(Vector2 sc);
    void setScale(float x, float y);

    static void ConvertToLua(lua_State* state);

protected:
    Vector2 mPosition_;
    Vector2 mScale_;
    float mRotation_;
};

