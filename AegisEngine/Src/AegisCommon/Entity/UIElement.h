#pragma once 

#include "../Interfaces/ILuaObject.h"
#include <unordered_map>
#include "../Components/UIComponent.h"

class RectTransform;
class Canvas;
class Vector2;
class UIElement :
	public ILuaObject
{
private:
	std::string mName_; //name of the entity, works like a tag, useful to debug
	RectTransform* mTransform_;
	Canvas* mCanvas_;

protected:
	std::unordered_map <std::string, UIComponent*> mComponents_; //list of all the components in scene
	std::vector<UIComponent*> mComponentsArray_; //list of all the components in scene
	bool active_; //bool to check if the entity is active or not
public:
	UIElement(Canvas* scene, Vector2 pos);
	~UIElement();

	void init();
	void render();

	void OnClickUp();
	void OnClickDown();

	void OnMouseOver();
	void OnMouseExit();

	void addComponent(UIComponent* component);

	template <typename T>
	inline T* getComponent(const char* componentName);

	inline void addComponentFromLua(UIComponent* component);
	UIComponent* getComponentLua(std::string componentName);

	RectTransform* getRectTransform() const;
	void setRectTransform(RectTransform* tr);

	void destroy();

	static void ConvertToLua(lua_State* state);

	std::string getName() const;
	void setName(std::string name);

	inline Canvas* getCanvas() const { return mCanvas_; }
	inline void setCanvas(Canvas* canvas) { mCanvas_ = canvas; }
};

