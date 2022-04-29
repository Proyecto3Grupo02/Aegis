#pragma once 

#ifndef _RECT_TRANSFORM
#define _RECT_TRANSFORM

#include "UIComponent.h"
#include "../Utils/Vector2.h"
enum Aligment{
    TopLeft,
    MidLeft,
    BottomLeft,

    TopCenter,
    MidCenter,
    BottomCenter,

    TopRight,
    MidRight,
    BottomRight,
    NONE
};
class Vector2;
class RectTransform: public UIComponent
{
private:
    Aligment mAligment_;

    Vector2 mPosition_;
    Vector2 mScale_;
    float mRotation_;

public:
    RectTransform(UIElement* elem, Vector2 pos, Vector2 scale, float rotation);
    ~RectTransform() = default;

    inline Vector2 getPosition()const { return mPosition_; }
    void setPosition(float x, float y) { mPosition_ = Vector2(x, y); }

    inline Vector2 getScale() const { return mScale_; }
    void setScale(float x, float y) { mScale_ = Vector2(x, y); }

    inline float getRotation() const { return mRotation_; }
    void setRotation(float rotation) { mRotation_ = rotation; }

};



#endif