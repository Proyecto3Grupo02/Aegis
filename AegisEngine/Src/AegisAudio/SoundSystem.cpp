#include "SoundSystem.h"
#include <fmod_errors.h>
#include "DebugManager.h"
SoundSystem::SoundSystem(std::string soundsPath) :
	system(nullptr),
	listener(nullptr),
	music(nullptr),
	soundEffects(nullptr),
	SR(new SoundResources(soundsPath))
{
	generalVolume = 1;
	musicVolume = 1;
	soundVolume = 1;

	// Error codes are stored in result
	// We create and check all the system while we create them
	FMOD_RESULT result = FMOD::System_Create(&system);
	ERRCHECK(result);
	result = system->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
	
	result = system->createChannelGroup("music", &music);
	ERRCHECK(result);
	result = system->createChannelGroup("soundEffect", &soundEffects);
	ERRCHECK(result);

	ChannelGroup* master;
	result = system->getMasterChannelGroup(&master);
	ERRCHECK(result);
	result = master->addGroup(music);
	ERRCHECK(result);
	result = master->addGroup(soundEffects);
	ERRCHECK(result);

	Debug()->log("SOUND SYSTEM: System started");
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
FMOD::Channel* SoundSystem::playSound(const std::string& name)
{
	Channel* channel;
	Sound* sound = getSound(name);
	if (sound == nullptr) return nullptr;

	FMOD_RESULT result = system->playSound(sound, soundEffects, false, &channel);
	ERRCHECK(result);
	channel->set3DMinMaxDistance(50, 10000);
	return channel;
}

/// <summary>
/// Plays the music
/// </summary>
/// <param name="name"> Song name </param>
FMOD::Channel* SoundSystem::playMusic(const std::string& name)
{
	Channel* channel;
	Sound* sound = getSound(name);
	if (sound == nullptr) return nullptr;

	FMOD_RESULT result = system->playSound(sound, music, false, &channel);
	ERRCHECK(result);
	channel->set3DMinMaxDistance(50, 10000);
	return channel;
}

/// <summary>
/// Sets all audio to pause, apart from their sound groups
/// </summary>
/// <param name="pause"> True o false </param>
void SoundSystem::setPauseAllSounds(bool pause)
{
	ChannelGroup* master;

	FMOD_RESULT result = system->getMasterChannelGroup(&master);
	ERRCHECK(result);

	master->setPaused(pause);
}

/// <summary>
/// Sets the MUSIC volume
/// </summary>
/// <param name="volume"> Volume in % </param>
void SoundSystem::setMusicVolume(float volume)
{
	music->setVolume(volume);
	musicVolume = volume;
}

/// <summary>
/// Sets the EFFECT volume
/// </summary>
/// <param name="volume"> Volume in % </param>
void SoundSystem::setSoundEffectsVolume(float volume)
{
	soundEffects->setVolume(volume);
	soundVolume = volume;
}

/// <summary>
/// Sets all volumes
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

float SoundSystem::getMusicVolume() const
{
	return musicVolume;
}

float SoundSystem::getSoundVolume() const
{
	return soundVolume;
}

/// <summary>
/// Removes an emitter from the array
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

void SoundSystem::stopMusic(const std::string& name)
{
	Channel* channel;
	Sound* sound = getSound(name);
	if (sound == nullptr) return;

	FMOD_RESULT result = system->playSound(sound, soundEffects, false, &channel);
	ERRCHECK(result);
	channel->setPaused(true);

}

void SoundSystem::stopSound(const std::string& name)
{
	Channel* channel;
	Sound* sound = getSound(name);
	if (sound == nullptr) return;

	FMOD_RESULT result = system->playSound(sound, soundEffects, false, &channel);
	ERRCHECK(result);
	channel->setPaused(true);

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
		pos = *listener->position;

		//float z = listener->position->GetZ();
		//float y = listener->position->GetY();

		float z = listener->quaternion->getZ();
		float y = listener->quaternion->getY();
		forward = Vector3{ 0, 0, z }; //Vector3 Forward
		up = Vector3{ 0, y ,0 }; // Vector3 Up
		setListenerAttributes(pos, forward, up);
	}
	// Emitters position update
	FMOD_VECTOR emitterPosition, zero;
	zero = { 0,0,0 };
	for (int i = 0; i < emitters.size(); i++)
	{
		bool paused = true;
		SoundSystem::EmitterData* data = emitters[i];
		for (auto it = data->channels.begin(); it != data->channels.end(); it++) {
			bool aux = (*it).second->paused;
			paused = paused && aux;
			if (!aux)
				(*it).second->channel->set3DAttributes(&emitterPosition, &zero);
		}
		Vector3 pos = *data->position;
		if (!paused) emitterPosition = vecToFMOD(pos);
	}

	FMOD_RESULT result = system->update();
	ERRCHECK(result);
}

/// <summary>
/// Adds an emitter to the list
/// </summary>
/// <param name="position"> Vector3 with the position of the Object its part from </param>
SoundSystem::EmitterData* SoundSystem::createEmitter(const Vector3* position)
{
	SoundSystem::EmitterData* data = new SoundSystem::EmitterData(position);
	emitters.push_back(data);
	return data;
}

/// <summary>
/// Creates the listener, using a queaternion for orientation and position
/// </summary>
/// <param name="position"> Necesita ubicancia </param>
/// <param name="quaternion"> Necesita orientacion </param>
/// <returns></returns>
SoundSystem::ListenerData* SoundSystem::createListener(Vector3* position, Vector4* quaternion)
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
		Debug()->log(FMOD_ErrorString(result));
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
		Debug()->log("SOUND MANAGER: Error playing sound %s" + errLog);
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
		delete channel;
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
	delete position;
	position = nullptr;
}

/// <summary>
/// Metodo para modificar si es necesario por herencia
/// </summary>
/// <param name="position"></param>
SoundSystem::EmitterData::EmitterData(const Vector3* position) : position(position), channels(std::map<std::string, SoundChannel*>())
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

void SoundSystem::ConvertToLua(lua_State* state) {
	getGlobalNamespace(state).
		beginNamespace("Aegis").
		beginClass<SoundSystem>("SoundManagerClass").
		addProperty("generalVolume", &SoundSystem::getGeneralVolume, &SoundSystem::setGeneralVolume).
		addProperty("musicVolume", &SoundSystem::getMusicVolume, &SoundSystem::setMusicVolume).
		addProperty("SFXVolume", &SoundSystem::getSoundVolume, &SoundSystem::setSoundEffectsVolume).
		endClass().
		endNamespace();

	exportToLua(SoundSystem::getInstance(), "SoundManager");

}