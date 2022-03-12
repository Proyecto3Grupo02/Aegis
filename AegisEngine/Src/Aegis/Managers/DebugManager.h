#pragma once

#ifndef DEBUG
#define DEBUG

#include "Singleton.h"
#include <string>
#include <OgreManualObject.h>
#include<vector>

#include "Vector3.h"

class DebugManager: public Singleton<DebugManager>{
public:
    DebugManager();
    virtual ~DebugManager();

    //write in console info
    void Log(const std::string& msg);
    
    //write in console an error
    void LogError(const std::string& error);

    //write in console a warning
    void LogWarning(const std::string& error);

    //shows delta time num of entities 
    void showInfo();

    void drawLine(Vector3 origin, Vector3 end, Vector3 color);

protected:
    Ogre::ManualObject* mLines_;


};

#endif

