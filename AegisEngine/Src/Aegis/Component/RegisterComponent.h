//#pragma once
//
//#include "ComponentManager.h"
//
//#define To_String(x) #x
//#define Link_This(x) int link_##x=0;
//
//#define RegisterFactory(cmp)\
//LinkThis(cmp);\
//class Register_##cmp{\
//public:\
//	Register_##cmp(){\
//		ComponentManager::getInstance()->registerComponent<cmp>(To_String(cmp));\
//	}\
//};\
//Register_##cmp register_##cmp = Register_##cmp();