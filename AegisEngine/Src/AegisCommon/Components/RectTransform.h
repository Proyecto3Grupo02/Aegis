#pragma once 

#ifndef _RECT_TRANSFORM
#define _RECT_TRANSFORM

#include "UIComponent.h"

enum Aligment{
    TopLeft,
    MidLeft,
    BottomLeft,

    TopCenter,
    MidCenter,
    BottomCenter,

    TopRight,
    MidRight,
    BottomRight
};
class Vector2;
class RectTransform: public UIComponent
{
private:
    Aligment mAligment_;

    Vector2 mPosition_;
    float mRotation_;
    


public:
    RectTransform(/* args */);
    ~RectTransform();



};



#endif