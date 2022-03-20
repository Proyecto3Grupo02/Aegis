#pragma once

#ifndef LUA_MANAGER
#define LUA_MANAGER
#include "Singleton.h"

namespace Lua{
    class LuaScript;
}
class LuaManager: public Singleton<LuaManager>{
public:
    LuaManager();
    virtual ~LuaManager();


};


#endif