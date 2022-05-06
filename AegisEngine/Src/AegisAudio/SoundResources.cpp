#include "SoundResources.h"
//using namespace std;
#include <dirent.h>
#include "DebugManager.h"
SoundResources::SoundResources()
{
	ParseDirectory(rutaArchivo);
}

SoundResources::~SoundResources()
{
}

void SoundResources::ParseDirectory(std::string dir)
{
	DIR* dirp;
	struct dirent* dp;
	dirp = opendir(dir.c_str());
	if (dirp == NULL)
	{
		Debug()->Log("Error al abrir el directorio");
		return;
	}


	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_type == DT_DIR)
		{
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
			{
				std::string subdir = dir + "/" + dp->d_name;
				ParseDirectory(subdir);
			}
		}
		else
		{
			std::string file = dp->d_name;
			std::string extension = file.substr(file.find_last_of(".") + 1);
			if (extension == "wav" || extension == "ogg" || extension == "mp3")
			{
				std::string path = dir + "/" + file;
				std::fstream todo;
				todo.open(path, std::ios::in);
				if (!todo) {
					Debug()->Log("El archivo " + file + " no existe");
				}
				auto e = std::make_pair(file.substr(0, file.find_last_of(".")), path);
				mapSound.insert(e);
			}
		}
	}

	closedir(dirp);
}

std::string SoundResources::getSong(std::string song)
{
	auto it = mapSound.find(song);

	return it->second;
}

