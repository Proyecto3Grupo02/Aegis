#include "SoundSystem.h"
#include <fmod_errors.h>
#include "DebugManager.h"
#include <algorithm>
#include <functional>

SoundSystem::SoundSystem(std::string soundsPath) :
	system(nullptr),
	listener(nullptr),
	SR(new SoundResources(soundsPath))
{
	generalVolume = 1;

	// Error codes are stored in result
	// We create and check all the system while we create them
	FMOD_RESULT result = FMOD::System_Create(&system);
	ERRCHECK(result);
	result = system->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	DebugManager::getInstance()->log("SOUND SYSTEM: System started");
}

SoundSystem::~SoundSystem()
{
	close();
}

/// <summary>
/// Se llamara al cerrar el juego, descarta los emisores y el receptor
/// </summary>
void SoundSystem::close() {
	for (EmitterData* emitter : emitters)
		removeEmitter(emitter);

	removeListener();

	system->close();
	system->release();
	channelGroups.clear();
	if (SR != nullptr)
		delete SR;
}

/// <summary>
/// Devuelve el tipo sonido si no da fallo al cargarlo
/// </summary>
/// <param name="name"> Nombre del efecto </param>
/// <param name="mode"> Modo de sonido (Loop, default etc) </param>
/// <returns></returns>
Sound* SoundSystem::createSound(const std::string& name, SoundMode mode)
{
	Sound* sound;
	if (system->createSound(name.c_str(), mode, nullptr, &sound) == FMOD_RESULT::FMOD_OK)
		return sound;
	return nullptr;
}

/// <summary>
/// Ejecuta el sonido
/// </summary>
/// <param name="name"> Nombre del efecto </param>
/// <returns></returns>
FMOD::Channel* SoundSystem::playSound(const std::string& name, const std::string& channelName)
{
	Channel* channel;
	Sound* sound = getSound(name);
	if (sound == nullptr) return nullptr;

	FMOD_RESULT result = system->playSound(sound, getChannelGroup(channelName), false, &channel);
	ERRCHECK(result);
	return channel;
}

void SoundSystem::updatePosition(EmitterData* emitterName, Vector3 position)
{
	emitterName->position = vecToFMOD(position);
}

/// <summary>
/// Sets all audio to pause, apart from their sound groups
/// </summary>
/// <param name="pause"> True o false </param>
void SoundSystem::setPauseAllSounds(bool pause)
{
	ChannelGroup* master;	// Master channel group is a default FMOD channel group

	FMOD_RESULT result = system->getMasterChannelGroup(&master);
	ERRCHECK(result);

	master->setPaused(pause);
}

/// <summary>
/// Sets ALL volumes
/// </summary>
/// <param name="volume"> Volume in % </param>
void SoundSystem::setGeneralVolume(float volume)
{
	ChannelGroup* master;

	FMOD_RESULT result = system->getMasterChannelGroup(&master);
	ERRCHECK(result);

	master->setVolume(volume);
	generalVolume = volume;
}

void SoundSystem::setChannelVolume(float volume, const std::string& channel)
{
	auto it = channelGroups.find(channel);
	if (it != channelGroups.end())
		(*it).second->setVolume(volume);
}

float SoundSystem::getChannelVolume(const std::string channel)
{
	float volume = 0;
	auto it = channelGroups.find(channel);
	if (it != channelGroups.end())
		(*it).second->getVolume(&volume);
	return volume;
}

/// <summary>
/// Sets the Camera/Player variables for 3D sound
/// </summary>
/// <param name="position"> Camera/Player Position </param>
/// <param name="forward"> Vector on X axis "points forward" </param>
/// <param name="up"> Vector on Y axis "points up" </param>
void SoundSystem::setListenerAttributes(Vector3& position, Vector3& forward, Vector3& up)
{
	FMOD_VECTOR pos, vel, forwardTmp, upTmp;
	pos = { float(position.getX()) ,float(position.getY()) ,float(position.getZ()) };
	vel = { 0,0,0 };
	forwardTmp = { float(forward.getX()) ,float(forward.getY()) ,float(forward.getZ()) };
	upTmp = { float(up.getX()) ,float(up.getY()) ,float(up.getZ()) };
	system->set3DListenerAttributes(0, &pos, &vel, &forwardTmp, &upTmp);
}

float SoundSystem::getGeneralVolume() const
{
	return generalVolume;
}

/// <summary>
/// Removes an emitter from the vector
/// </summary>
/// <param name="emitter"> Emitter to be removed </param>
void SoundSystem::removeEmitter(EmitterData* emitter)
{
	auto it = std::find(emitters.begin(), emitters.end(), emitter);
	if (it != emitters.end())
	{
		delete* it;
		emitters.erase(it);
	}
}


/// <summary>
/// Searchs the given channel by name in the given emitter
/// </summary>
void SoundSystem::stopChannel(EmitterData* emitterData, const std::string& name)
{
	auto it = emitterData->channels.find(name);
	if (it != emitterData->channels.end()) {
		it->second->channel->stop();
		delete it->second;
		emitterData->channels.erase(it);
	}
}



/// <summary>
/// Updates position of the Listener and Emitters for 3D sound
/// </summary>
/// <param name="deltaTime"> Actual elapsed time </param>
void SoundSystem::update(float deltaTime)
{
	Vector3 pos, forward, up;
	// Listener position and quaternion update
	if (listener != nullptr)
	{
		pos = listener->position;

		float z = listener->quaternion.getZ();
		float y = listener->quaternion.getY();
		forward = Vector3{ 0, 0, z };	//	Vector3 Forward
		up = Vector3{ 0, y ,0 };		//	Vector3 Up
		setListenerAttributes(pos, forward, up);
	}

	// Emitters position update
	FMOD_VECTOR zero;
	zero = { 0,0,0 };
	for (int i = 0; i < emitters.size(); i++)
	{
		SoundSystem::EmitterData* data = emitters[i];

		for (auto it = data->channels.begin(); it != data->channels.end(); it++) {
			if (!(*it).second->paused)
				(*it).second->channel->set3DAttributes(&data->position, &zero);
		}
	}

	FMOD_RESULT result = system->update();
	ERRCHECK(result);
}

FMOD::ChannelGroup* SoundSystem::getChannelGroup(const std::string channelName)
{
	auto it = channelGroups.find(channelName);

	if (it == channelGroups.end())
	{
		channelGroups.insert({ channelName, nullptr });
		auto result = system->createChannelGroup(channelName.c_str(), &channelGroups.at(channelName));
		ERRCHECK(result);
		ChannelGroup* master;
		result = system->getMasterChannelGroup(&master);
		ERRCHECK(result);
		result = master->addGroup(channelGroups.at(channelName));
		ERRCHECK(result);
	}
	return channelGroups.at(channelName);

	return nullptr;
}

SoundSystem::SoundChannel* SoundSystem::createSoundChannel(Channel* channel)
{
	return new SoundSystem::SoundChannel(channel);
}


/// <summary>
/// Adds an emitter to the list
/// </summary>
/// <param name="position"> Vector3 with the position of the Object its part from </param>
SoundSystem::EmitterData* SoundSystem::createEmitter(Vector3 position)
{
	SoundSystem::EmitterData* data = new SoundSystem::EmitterData(vecToFMOD(position));
	emitters.push_back(data);
	return data;
}

/// <summary>
/// Creates the listener, using a queaternion for orientation and position
/// </summary>
/// <param name="position"> Necesita ubicancia </param>
/// <param name="quaternion"> Necesita orientacion </param>
/// <returns></returns>
SoundSystem::ListenerData* SoundSystem::createListener(Vector3 position, Vector4 quaternion)
{
	if (listener != nullptr)
		delete listener;
	ListenerData* data = new ListenerData();
	data->position = position;
	data->quaternion = quaternion;
	listener = data;
	return data;
}

/// <summary>
/// Removes Listener, which SHOULD be done only on destruction I guess 
/// (For legal reasons the "I guess" expression is only used for sarcastic value
/// I actually know it does that)
/// </summary>
void SoundSystem::removeListener()
{
	if (listener != nullptr)
	{
		delete listener;
		listener = nullptr;
	}
}

void SoundSystem::updateListener(Vector3 position, Vector4 quaternion)
{
	listener->position = position;
	listener->quaternion = quaternion;
}

/// <summary>
/// Transforms a Vector3 to FMOD_VECTOR
/// </summary>
/// <param name="in"> Vector3 from the Utils class </param>
/// <returns> Vector3 from the FMOD API </returns>
FMOD_VECTOR SoundSystem::vecToFMOD(Vector3& in)
{
	FMOD_VECTOR out;
	out.x = in.getX();
	out.y = in.getY();
	out.z = in.getZ();

	return out;
}

/// <summary>
/// FMOD Reverb
/// </summary>
FMOD::Reverb3D* SoundSystem::createReverb()
{
	FMOD::Reverb3D* reverb;

	FMOD_RESULT result = system->createReverb3D(&reverb);
	ERRCHECK(result);
	return reverb;
}


/// <summary>
/// When we check the errors the FMOD API returns a code with info
/// In the event of succes it returns FMOD_OK which we ignore
/// </summary>
void SoundSystem::ERRCHECK(FMOD_RESULT result) const
{
	// Sacado de los apuntes de cuarto, la verdad
	if (result != FMOD_RESULT::FMOD_OK)
		DebugManager::getInstance()->log(FMOD_ErrorString(result));
}

/// <summary>
/// Get sound from resources
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
Sound* SoundSystem::getSound(const std::string& name)
{

	Sound* sound = createSound(SR->getSong(name), FMOD_DEFAULT);
	if (sound == nullptr) return nullptr;

	// Wait till loaded
	FMOD_OPENSTATE state;
	FMOD_RESULT result;
	do {
		result = sound->getOpenState(&state, nullptr, nullptr, nullptr);
	} while (state == FMOD_OPENSTATE_LOADING);

	if (result != FMOD_OK) {
		std::string errLog = name.c_str();
		DebugManager::getInstance()->log("SOUND MANAGER: Error playing sound %s" + errLog);
		ERRCHECK(result);
		return nullptr;
	}

	return sound;
}

/// <summary>
/// Destructora de canales
/// </summary>
SoundSystem::SoundChannel::~SoundChannel()
{
	if (channel != nullptr)
	{
		channel = nullptr;
	}
}

/// <summary>
/// Metodo para modificar si es necesario por herencia
/// </summary>
/// <param name="position"></param>
SoundSystem::SoundChannel::SoundChannel() : channel(nullptr), paused(false)
{

}

/// <summary>
/// Metodo para modificar si es necesario por herencia
/// </summary>
/// <param name="position"></param>
SoundSystem::SoundChannel::SoundChannel(Channel* channel) : channel(channel), paused(false)
{

}

/// <summary>
/// Destructora de emisores
/// </summary>
SoundSystem::EmitterData::~EmitterData()
{
	for (auto it = channels.begin(); it != channels.end(); it++)
		delete it->second;
	channels.clear();
}

/// <summary>
/// Metodo para modificar si es necesario por herencia
/// </summary>
/// <param name="position"></param>
SoundSystem::EmitterData::EmitterData(FMOD_VECTOR pos) : position(pos), channels(std::map<std::string, SoundChannel*>())
{
}

/// <summary>
/// Metodo que comprueba si todos los emisores estan pausados
/// </summary>
/// <returns></returns>
bool SoundSystem::EmitterData::isPaused()
{
	auto it = channels.begin();
	bool paused = true;
	while (paused && it != channels.end()) {
		paused = (*it).second->paused;
		it++;
	}

	return paused;
}

void SoundSystem::pauseSound(EmitterData* emitterData, const std::string& name)
{
	auto it = emitterData->channels.find(name);
	if (it != emitterData->channels.end()) {
		it->second->paused = true;
		it->second->channel->setPaused(true);
	}
}

void SoundSystem::resumeSound(EmitterData* emitterData, const std::string& name)
{
	auto it = emitterData->channels.find(name);
	if (it != emitterData->channels.end()) {
		it->second->paused = false;
		it->second->channel->setPaused(false);
	}
}

void SoundSystem::ConvertToLua(lua_State* state) {
	getGlobalNamespace(state).
		beginNamespace("Aegis").
			beginClass<SoundSystem>("SoundManagerClass").
				addProperty("generalVolume", &SoundSystem::getGeneralVolume, &SoundSystem::setGeneralVolume).
				addFunction("GetChannelVolume", &SoundSystem::getChannelVolume).
				addFunction("SetChannelVolume", &SoundSystem::setChannelVolume).
				addFunction("PlayOneShot", &SoundSystem::playSound).
			endClass().
		beginClass< FMOD::Channel>("FMODChannel").
			addFunction("SetVolume", &FMOD::Channel::setVolume).
			addFunction("SetPaused", &FMOD::Channel::setPaused).
			addFunction("Stop", &FMOD::Channel::stop).
		addFunction("SetLoopCount",								// Funcion proxy, para no tener que declarar una funcion extra en SoundSystem
			std::function<void(FMOD::Channel* , int)>
			(
				[](FMOD::Channel* channel, int loopCount) 
				{
					channel->setMode(loopCount != 0 ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
					channel->setLoopCount(loopCount);
				}
			)).
		endClass().
		endNamespace();
}