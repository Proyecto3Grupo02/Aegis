#pragma once

#ifndef LUA_BASIC_H
#define LUA_BASIC_H
#include "Singleton.h"

#ifdef __cplusplus
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "LuaBridge.h"
#endif
#endif
