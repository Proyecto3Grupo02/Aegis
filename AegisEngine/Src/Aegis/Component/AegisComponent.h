#pragma once
#ifndef AEGIS_COMPONENT
#define AEGIS_COMPONENT
#include "Component.h"

namespace AegisEngine {
	class Entity;
	class AegisComponent : public Component {
	public:
		AegisComponent() : Component() {}
		~AegisComponent() {}
	};
}
#endif