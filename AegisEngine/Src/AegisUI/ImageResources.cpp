#include "ImageResources.h"
#include <cstdio>
#include <dirent.h>

using namespace std;

ImageResources::ImageResources()
{
}

ImageResources::~ImageResources()
{
	struct dirent* dp;
}

void ImageResources::ParseDirectory(std::string dir)
{
}

std::string ImageResources::getImage(std::string image_)
{
	auto it = mapImage.find(image_);

	return it->second;
}
