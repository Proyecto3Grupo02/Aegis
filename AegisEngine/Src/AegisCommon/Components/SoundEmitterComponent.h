#pragma once 

#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include "AegisComponent.h"

class SoundEmitterComponent : public AegisComponent
{
	public:

		SoundEmitterComponent(Entity* ent, std::string sound);
		~SoundEmitterComponent();
		void playMusic();
		void playSound();
		void stopMusic();
		void stopSound();

		std::string getSound() const;
		void setSound(std::string name);

		static void ConvertToLua(lua_State* state);
	private:
		std::string soundName;
};

#endif