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

    Vector3 mDiffuse_;
    Vector3 mSpecular_;

    AegisLight* mLight_;

    void initLight();
    void setLightOn() {
        mLight_->setLightOn();
    }
    void setLightOff() {
        mLight_->setLightOff();
    }
    

   
public:
    LightComponent(Entity* ent, LuaRef args);
    ~LightComponent();

    virtual void init() override {};


    inline Vector3 getLightColor() { return mDiffuse_; }
    void setLightColor(float r, float g, float b);

    inline Vector3 getSpecularColor() { return mSpecular_; }
    void setSpecularColor(float r, float g, float b);

    inline void setDirLight() {
        mLight_->setDirLight();
    }
    inline void setPointLight() {
        mLight_->setPointLight();
    }
    void setSpotLight() {
        mLight_->setSpotLight();
    }

    static void ConvertToLua(lua_State* state);


};





#endif