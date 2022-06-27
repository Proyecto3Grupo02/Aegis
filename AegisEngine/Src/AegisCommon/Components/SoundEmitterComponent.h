#pragma once 

#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include "AegisComponent.h"

class SoundEmitterComponent : public AegisComponent
{
	public:

		SoundEmitterComponent(Entity* ent, std::string sound, std::string mode);
		~SoundEmitterComponent();
		void playMusic();
		void playSound();
		void stop(const std::string name);
		virtual void update(float deltaTime);

		std::string getSound() const;
		void setSound(std::string name);

		static void ConvertToLua(lua_State* state);
	private:
		std::string soundName;
		SoundSystem::EmitterData* emitterData;

		// // Esto viene de SoundSystem y tiene los componentes
		//		std::map<std::string, SoundChannel*> channels;
		//		const Vector3* position;
};

#endif