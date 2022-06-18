#pragma once
#ifndef VECTOR2_H 
#define VECTOR2_H
#include "ILuaObject.h"

class Vector2
{
private:

public:
    Vector2(float _x, float _y) : x(_x), y (_y) {}
    Vector2(float all) : x(all), y(all) {}
	Vector2(): x(0), y(0) {}
    ~Vector2() {};

    float GetX() const{return x;}    
    float GetY() const{return y;}

    void SetX(float _x){x=_x;}
    void SetY(float _y){y=_y;}

    Vector2 operator+(Vector2 const& v){ return Vector2(x+v.x, y + v.y);}
    Vector2 operator-(Vector2 const& v){ return Vector2(x-v.x, y - v.y);}
    Vector2 operator*(float const& f) const { return Vector2(x * f, y * f); }
	Vector2 operator/(float const& f) const { return Vector2(x / f, y / f); }
	
    Vector2 operator%(float const& f) const { return Vector2(fmod(x,f), fmod(y, f)); }
	
    static void ConvertToLua(lua_State* state){
        getGlobalNamespace(state).
        beginNamespace("Aegis").
        beginNamespace("Maths").
        beginClass<Vector2>("Vector2").
        addConstructor<void(*)(float, float)>().
        addProperty("x", &Vector2::GetX, &Vector2::SetX).
        addProperty("y", &Vector2::GetY, &Vector2::SetY).
        addFunction("__add", &Vector2::operator+).
        addFunction("__sub", &Vector2::operator-).
        addFunction("__mul", &Vector2::operator*).
        addFunction("__div", &Vector2::operator/).
        endClass().
        endNamespace().
        endNamespace();
        
    }

    float x;
    float y;
    
};

#endif