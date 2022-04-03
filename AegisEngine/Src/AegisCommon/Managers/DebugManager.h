#pragma once

#ifndef DEBUG
#define DEBUG

#include "../Utils/Singleton.h"
#include "../Interfaces/IInitializable.h"
#include "../Utils/Vector3.h"
#include "../../checkML.h" //BASURA
#include <string>
#include<vector>

class DebugManager: public Singleton<DebugManager>, public IInitializable{
public:
    DebugManager();
    virtual ~DebugManager();

    //write in console info
    void Log(const std::string& msg);
    
    //write in console an error
    void LogError(const std::string& error);

    //write in console a warning
    void LogWarning(const std::string& error);

    //shows delta time, num of entities... 
    void showInfo();

    

    bool Init();

protected:
};

inline DebugManager* Debug() {
    return DebugManager::getInstance();
}
#endif

