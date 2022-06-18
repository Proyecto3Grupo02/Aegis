#include "ImageResources.h"
#include "dirent.h"
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
	DIR* dirp;
	struct dirent* dp;
	dirp = opendir(dir.c_str());
	if (dirp == NULL)
	{
		std::cout<<"Error al abrir el directorio \n";
		return;
	}


	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_type == DT_DIR)
		{
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
			{
				string subdir = dir + "/" + dp->d_name;
				ParseDirectory(subdir);
			}
		}
		else
		{
			std::string file = dp->d_name;
			std::string extension = file.substr(file.find_last_of(".") + 1);
			if (extension == "png" || extension == "jpg")
			{
				std::string path = dir + "/" + file;
				std::fstream todo;
				todo.open(path, std::ios::in);
				if (!todo) {
					std:: cout<<("El archivo " + file + " no existe");
				}
				auto e = std::make_pair(file.substr(0, file.find_last_of(".")), path);
				mapImage.insert(e);
			}
		}
	}

	closedir(dirp);
}

std::string ImageResources::getImage(std::string image_)
{
	auto it = mapImage.find(image_);

	return it->second;
}
