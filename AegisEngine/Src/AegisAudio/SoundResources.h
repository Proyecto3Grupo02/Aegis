#pragma once
#ifndef SOUND_RESOURCES_H
#define SOUND_RESOURCES_H

#include <vector>
using namespace std;

class SoundResources
{
public:
	SoundResources();
	~SoundResources();

private:
	vector<string> vectorSound;
	string ruta;
};

SoundResources::SoundResources()
{
}

SoundResources::~SoundResources()
{
}

#endif