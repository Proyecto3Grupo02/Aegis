#include "UIElement.h"
#include "../Utils/Vector2.h"
#include "../Components/UIComponent.h"
#include "../Components/RectTransform.h"
UIElement::UIElement(Scene* scene, Vector2 pos):
	mScene_(mScene_)
{
	mTransform_ = new RectTransform(this, pos, Vector2(1,1),0);
	this->addComponentFromLua(mTransform_);
}

UIElement::~UIElement()
{
	for (Component* c : mComponentsArray_)
		delete c;
	mComponentsArray_.clear();
	mComponents_.clear();
	destroy();
}

void UIElement::init()
{
	for (Component* c : mComponentsArray_) {
		c->init();
	}
}

void UIElement::render()
{
	if (active_) {
		for (auto component : mComponentsArray_) {
			if (!component->getActive()) continue;
			component->render();
		}
	}
}

inline void UIElement::addComponentFromLua(UIComponent* component)
{
	std::string key = component->GetComponentName();

	if (mComponents_.count(key) == 0) { //si no est� lo a�adimos
		//component->SetEntity(this);

		mComponentsArray_.push_back(component);
		mComponents_[key] = component;
	}
	else
	{
		std::cout << key << " is already in " << mName_ << ", component will be deleted";
		delete component;
	}
}

UIComponent* UIElement::getComponentLua(std::string componentName)
{

	if (mComponents_.count(componentName) == 0)
		return nullptr;
	else return  mComponents_[componentName];
}

RectTransform* UIElement::getRectTransform() const
{
	return mTransform_;
}

void UIElement::setRectTransform(RectTransform* tr)
{
	mTransform_ = tr;
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

template<typename T>
inline T* UIElement::addComponent(const char* componentName)
{
	return nullptr;
}

template<typename T>
inline T* UIElement::getComponent(const char* componentName)
{
	return nullptr;
}