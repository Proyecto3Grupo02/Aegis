#pragma once

#ifndef COMPONENT_REGISTER
#define COMPONENT_REGISTER

#include "ComponentManager.h"

#define TO_STRING(x) #x

#define FORCE_LINK_THIS(x) int force_link_##x = 0;
#define REGISTER_FACTORY (cmp)\
FORCE_LINK_THIS(cmp);\
class Register_##tipo { \
	public:\
		Register_##tipo() {\
			ComponentManager::getInstance()->registerComponent<tipo>(TO_STRING(tipo));\
		}\
};\
Register_##cmp register_##cmp = Register_##cmp();

#endif