#include "RectTransform.h"

RectTransform::RectTransform(UIElement* mElem, Vector2 pos, Vector2 scale, float rotation):
	UIComponent("RectTransform", mElem), mPosition_(pos), mScale_(scale), mRotation_(rotation)
{
}

