#include "UIElement.h"
#include "../Utils/Vector2.h"
#include "../Components/RectTransform.h"
UIElement::UIElement(Canvas* canvas, Vector2 pos):
	mCanvas_(canvas)
{
	mTransform_ = new RectTransform(this,pos, Vector2(), 0);
}

UIElement::~UIElement()
{

}

void UIElement::init()
{
	for (Component* c : mComponentsArray_)
		c->init();
}

void UIElement::OnClickUp()
{
	if (!active_) {
		for (auto cmp : mComponentsArray_) {
			if (!cmp->getActive())
				continue;
			cmp->OnClickUp(this);
		}
	}
}

void UIElement::OnClickDown()
{
	if (!active_) {
		for (auto cmp : mComponentsArray_) {
			if (!cmp->getActive())
				continue;
			cmp->OnClickDown(this);
		}
	}
}

void UIElement::OnMouseOver()
{
}

void UIElement::OnMouseExit()
{
}

void UIElement::destroy()
{
}

void UIElement::ConvertToLua(lua_State* state)
{
}

std::string UIElement::getName() const
{
	return mName_;
}

void UIElement::setName(std::string name)
{
	mName_ = name;
}
