#pragma once
#ifndef IMAGE_RESOURCES_H
#define IMAGE_RESOURCES_H

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <sys/stat.h>
#include <filesystem>
#include <map>
#include "../AegisCommon/Managers/DebugManager.h"

typedef std::string image;

class ImageResources
{
private:
    std::map<image,std::string> mapImage;
    std::string route = "../Assets/Audios";
public:
    ImageResources();
    ~ImageResources();

    void ParseDirectory(std::string dir);
	std::string getImage(std::string image_);
};
#endif