
#include "Component.h"
#include "Entity.h"

Component::Component(Entity* entity): 
	mEntity_(entity), isActive_(true)
{
	
}

