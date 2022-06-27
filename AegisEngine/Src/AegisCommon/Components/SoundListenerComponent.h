#ifndef SOUND_LISTENER_H
#define SOUND_LISTENER_H

#include "AegisComponent.h"
#include "ILuaObject.h"

class TransformComponent;

class SoundListenerComponent: public AegisComponent
{
public:
    SoundListenerComponent(Entity* ent);
    virtual ~SoundListenerComponent();

    virtual void update(float deltaTime) override;

    static void ConvertToLua(lua_State* state);
private:
    TransformComponent* transform;
};

#endif