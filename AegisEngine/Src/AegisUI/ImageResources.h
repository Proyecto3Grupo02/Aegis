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

typedef std::string image;

class ImageResources
{
private:
    std::map<image,std::string> mapImage;
    std::string route = "../Assets/Textures";
public:
    ImageResources();
    ~ImageResources();

    void parseDirectory(std::string dir);
	std::string getImage(std::string image_);
};
#endif