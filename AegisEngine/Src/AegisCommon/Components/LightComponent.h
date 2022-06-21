#pragma once 

#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "AegisComponent.h"
#include "TransformComponent.h"
#include "Vector3.h"
#include "AegisLight.h"

class LightComponent: public AegisComponent
{
private:

    Vector3 mDiffuse_;
    Vector3 mSpecular_;

    AegisLight* mLight_;

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

    Vector3 getLightColor() const;
    void setLightColor(Vector3 diffuse);

    inline Vector3 getSpecularColor() const;
    void setSpecularColor(Vector3 spec);

    void setDirLight();
    void setPointLight();
    void setSpotLight();
    void setLightType(std::string lightType);
    void setDirection(Vector3 dir);

    static void ConvertToLua(lua_State* state);
};

#endif