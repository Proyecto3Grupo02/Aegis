#pragma once 

#ifndef LIGHT_H
#define LIGHT_H
#include "AegisComponent.h"
#include "Transform.h"

#include "../../AegisCommon/Utils/Vector3.h"

#include "../../AegisGraphics/Components/Light.h"


class LightComponent: public AegisComponent
{
private:
    Vector3 mAmbient_;
    Vector3 mDiffuse_;
    Vector3 mSpecular_;

    AegisLight* mLight_;

    void initLight();
    

   
public:
    LightComponent(Entity* ent, Vector3 amb, Vector3 diff, Vector3 spec);
    ~LightComponent();

    virtual void init() override {};

    static void ConvertToLua(lua_State* state);


};





#endif