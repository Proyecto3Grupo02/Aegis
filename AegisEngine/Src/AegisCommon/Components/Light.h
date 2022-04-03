#pragma once 

#ifndef LIGHT_H
#define LIGHT_H
#include "AegisComponent.h"
#include "Transform.h"

#include "../../AegisCommon/Utils/Vector3.h"

class Light: public AegisComponent
{
private:
    Vector3 mAmbient_;
    Vector3 mDiffuse_;
    Vector3 mSpecular_;

    Transform* mTr_;
    Ogre::Light* mLight_;
    Ogre::SceneManager* mngr_;
public:
    Light();
    Light(Vector3 amb, Vector3 diff, Vector3 spec, Ogre::SceneManager* sceneMng);
    ~Light();

    Vector3 getAmbient() { return mAmbient_; }
    Vector3 getDiffuse() { return mDiffuse_; }
    Vector3 getSpecular() { return mSpecular_; }
   
    void setAmbient(Vector3 amb) { mAmbient_ = amb; renderLight(); }
    void setDiffuse(Vector3 diff) { mDiffuse_ = diff; renderLight(); }
    void setSpecular(Vector3 spec) { mSpecular_ = spec; renderLight(); }

    virtual void init() override;
    void renderLight();

    static void ConvertToLua(lua_State* state);

};




#endif