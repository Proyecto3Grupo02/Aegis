#pragma once 

#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include "AegisComponent.h"
#include "SoundSystem.h"

class SoundEmitterComponent : public AegisComponent
{
public:
	struct FloatPair
	{
	public:
		float x, y;
	};

	struct SoundEmitterComponentData
	{
	public:
		std::string sound;
		std::string channelName;
		FloatPair minMax3DDistance;
		float volume;
		int loopCount;
		float pitch;
		bool playOnInit;
	};

public:
	SoundEmitterComponent(Entity* ent, SoundEmitterComponentData data);
	~SoundEmitterComponent();
	virtual void init() override;
	void playSound();
	void stop();
	void pause();
	void resume();
	void setChannelProperties(Channel* channel);
	virtual void update(float deltaTime);
	
	int getLoopCount() const;
	void setLoopCount(int loopCount);

	float getVolume() const;
	void setVolume(float volume);

	float getPitch() const;
	void setPitch(float pitch);

	std::string getSound() const;
	void setSound(std::string name);

	std::string getChannelName() const;
	void setChannelName(const std::string& name);

	static void ConvertToLua(lua_State* state);
private:
	SoundSystem::EmitterData* emitterData;
	SoundEmitterComponentData soundEmitterData;
	// // Esto viene de SoundSystem y tiene los componentes
	//		std::map<std::string, SoundChannel*> channels;
	//		const Vector3* position;
};

#endif