#pragma once

#ifndef AEGIS_MAIN_H 
#define AEGIS_MAIN_H

#include "IInitializable.h" 
#include "GameConfig.h"

class OgreWrapper;

class AegisMain : IInitializable
{
private:
	bool exit;

	void gameLoop();
	void convertObjectToLua();
	GameConfig* searchConfig();
	std::string searchFile(std::string path, std::string file);

public:
	AegisMain();
	virtual ~AegisMain();
	virtual bool init() override;
	void startGame();
	const float TARGET_FRAME_RATE = 60.0f;
	void free();
};
#endif //