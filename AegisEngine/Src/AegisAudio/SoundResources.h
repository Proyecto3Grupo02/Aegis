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

//#include "../checkML.h"

typedef	std::string cancion;

class SoundResources
{
public:
	SoundResources(std::string soundsPath);
	~SoundResources();
	void parseDirectory(std::string dir);
	std::string getSong(std::string song);
private:
	std::map<cancion,std::string> mapSound;
};


#endif