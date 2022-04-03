#pragma once
#ifndef SOUND_RESOURCES_H
#define SOUND_RESOURCES_H

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <sys/stat.h>
#include <filesystem>
#include <map>
#include "../AegisCommon/Managers/DebugManager.h"

typedef	std::string cancion;

class SoundResources
{
public:
	SoundResources();
	~SoundResources();
	std::string getSong(std::string song);
private:
	std::map<cancion,std::string> mapSound;
	std::string rutaArchivo = "../../Exes/AegisEngine/x64/Assets/Audios";
};


#endif