#include "RectTransform.h"

RectTransform::RectTransform(UIElement* element, Vector2 pos, Vector2 scale, float rotation):
	UIComponent("RectTransform", element), mPosition_(pos), mScale_(scale), mRotation_(rotation)
{
}

