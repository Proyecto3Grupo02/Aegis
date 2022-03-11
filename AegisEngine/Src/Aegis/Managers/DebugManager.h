#pragma once


#ifndef DEBUG
#define DEBUG

#include "Singleton.h"
#include <string>


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


    template <typename T>
    void checknull();


};

#endif

