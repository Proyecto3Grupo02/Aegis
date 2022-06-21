#pragma once

#ifndef DEBUG
#define DEBUG

#include "Singleton.h"
#include "IInitializable.h"
#include "Vector3.h"

#include <string>
#include<vector>

class DebugManager: public Singleton<DebugManager>, public IInitializable{
public:
    DebugManager();
    virtual ~DebugManager();

    //write in console info
    void log(const std::string& msg);
    
    //write in console an error
    void logError(const std::string& error);

    //write in console a warning
    void logWarning(const std::string& error);

    //shows delta time, num of entities... 
    void showInfo();

    bool init();
};

inline DebugManager* Debug() {
    return DebugManager::getInstance();
}
#endif

