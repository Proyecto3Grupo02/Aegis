#pragma once
#ifndef UI_COMPONENT
#define UI_COMPONENT


#include "AegisComponent.h"
class UIComponent: public AegisComponent
{
private:
    /* data */
public:
    UIComponent(std::string componentName, Entity* ent);
    ~UIComponent();

    virtual void OnMouseEnter()=0;
    virtual void OnMouseStay()=0;
    virtual void OnMouseExit()=0;

    virtual void OnClickDown()=0;
    virtual void OnClickUp()=0;


};
#endif