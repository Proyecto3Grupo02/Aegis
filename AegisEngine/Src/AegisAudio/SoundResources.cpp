#include "SoundResources.h"

SoundResources::SoundResources()
{
	std::fstream archivo;
	std::string cancion;
	archivo.open(rutaArchivo + "SoundResources.txt", std::ios::in);

	if (!archivo) {
		std::cout << "El archivo no existe" << std::endl;
		Debug()->Log("El archivo no existe");
		std::cerr << "Error de carga de archivo de audio";
	}
	else {
		int i = 0;
		while (!archivo.eof())
		{
			std::string song;
			std::string path;

			getline(archivo, song);
			getline(archivo, path);
			//rutaArchivo = ../../Exes/AegisEngine/x64/Assets/Audios
			std::fstream todo;
			todo.open(rutaArchivo + path, std::ios::in);

			// Añadimos una comprobacion para saber si existe el archivo
			if (!todo) {
				Debug()->Log("El archivo " + song + " no existe");
			}

			auto e = std::make_pair(song, path);

			mapSound.insert(e);
		}
	}
	archivo.close();
}

SoundResources::~SoundResources()
{
}

std::string SoundResources::getSong(std::string song)
{
	auto it = mapSound.find(song);

	return it->second;
}

