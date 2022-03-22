#include "SoundSystem.h"

#include <fmod_errors.h>
//#include "DebugUtils.h"

// Asignacion inicial de variables
SoundSystem::SoundSystem() : system(nullptr), listener(nullptr), music(nullptr), soundEffects(nullptr)
{
}

// Destructora
SoundSystem::~SoundSystem()
{
}

// Iniciacion del SoundSystem
void SoundSystem::init()
{
	generalVolume = 1;
	musicVolume = 1;
	soundVolume = 1;

	FMOD_RESULT result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->init(128, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	result = system->createChannelGroup("music", &music);
	ERRCHECK(result);

	FMOD::ChannelGroup* master;
	result = system->getMasterChannelGroup(&master);
	ERRCHECK(result);

	result = master->addGroup(music);
	ERRCHECK(result);

	result = system->createChannelGroup("soundEffect", &soundEffects);
	ERRCHECK(result);

	result = master->addGroup(soundEffects);
	ERRCHECK(result);

	LOG("SOUND SYSTEM: System started");
}
/// <summary>
/// Se llamara al cerrar el juego, descarta los emisores y el receptor
/// </summary>
void SoundSystem::close()
{
	for (EmitterData* emitter : emitters)
		removeEmitter(emitter);

	removeListener();

	system->close();
	system->release();

	destroy();
}
/// <summary>
/// Devuelve el tipo sonido si no da fallo al cargarlo
/// </summary>
/// <param name="name"> Nombre del efecto </param>
/// <param name="mode"> Modo de sonido (Loop, default etc) </param>
/// <returns></returns>
Sound* SoundSystem::createSound(const std::string& name, const SoundMode& mode)
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
/// Ejecuta la cancion
/// </summary>
/// <param name="name"> Nombre de la cancion </param>
/// <returns></returns>
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
/// Para detener todo el audio
/// </summary>
/// <param name="pause"> true o false </param>
void SoundSystem::setPauseAllSounds(bool pause)
{
	ChannelGroup* master;

	FMOD_RESULT result = system->getMasterChannelGroup(&master);
	
	ERRCHECK(result);

	master->setPaused(pause);
}

/// <summary>
/// Permite ajustar el volumen general de la musica
/// </summary>
/// <param name="volume"> Cantidad </param>
void SoundSystem::setMusicVolume(float volume)
{
	music->setVolume(volume);
	musicVolume = volume;
}

/// <summary>
/// Permite ajustar el volumen general de los efectos
/// </summary>
/// <param name="volume"> Cantidad </param>
void SoundSystem::setSoundEffectsVolume(float volume)
{
	soundEffects->setVolume(volume);
	soundVolume = volume;
}

/// <summary>
/// Permite ajustarel volumen general
/// </summary>
/// <param name="volume"> Cantidad </param>
void SoundSystem::setGeneralVolume(float volume)
{
	ChannelGroup* master;
	FMOD_RESULT result = system->getMasterChannelGroup(&master);

	ERRCHECK(result);

	master->setVolume(volume);
	generalVolume = volume;
}

/// <summary>
/// Ajusta las variables del listener/receptor
/// </summary>
/// <param name="position"> Vector3 de la posicion </param>
/// <param name="forward"> Vector3 de la direccion a la que apunta su eje ¿X?</param>
/// <param name="up"> Vector3 de la direccion a la que apunta su eje Y</param>
void SoundSystem::setListenerAttributes(const Vector3& position, const Vector3& forward, const Vector3& up)
{
	FMOD_VECTOR pos, vel, forwardTmp, upTmp;
	pos = { float(position.x) ,float(position.y) ,float(position.z) };
	vel = { 0,0,0 };
	forwardTmp = { float(forward.x) ,float(forward.y) ,float(forward.z) };
	upTmp = { float(up.x) ,float(up.y) ,float(up.z) };
	system->set3DListenerAttributes(0, &pos, &vel, &forwardTmp, &upTmp);
}

/// <summary>
/// Devuelve numericamente la potencia del volumen general
/// </summary>
/// <returns> float </returns>
float SoundSystem::getGeneralVolume() const
{
	return generalVolume;
}

/// <summary>
/// Devuelve numericamente la potencia del volumen musical
/// </summary>
/// <returns> float </returns>
float SoundSystem::getMusicVolume() const
{
	return musicVolume;
}

/// <summary>
/// Devuelve numericamente la potencia del volumen de los efectos
/// </summary>
/// <returns> float </returns>
float SoundSystem::getSoundVolume() const
{
	return soundVolume;
}

/// <summary>
/// Elimina un emisor
/// </summary>
/// <param name="emitter"> EmitterData </param>
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
/// Elimina el receptor
/// </summary>
void SoundSystem::removeListener()
{
	delete listener;
	listener = nullptr;
}

/// <summary>
/// Metodo que se llama en cada frame para actualizar el listener y los emisores
/// </summary>
/// <param name="deltaTime"> float necesario del deltaTime </param>
void SoundSystem::update(float deltaTime)
{
	Vector3 pos, forward, up;
	if (listener != nullptr)
	{
		pos = *listener->position;
		forward = GetForwardVector(*listener->quaternion);
		up = GetUpVector(*listener->quaternion);
		setListenerAttributes(pos, forward, up);
	}
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
		if (!paused) emitterPosition = vecToFMOD(*data->position);
	}

	FMOD_RESULT result = system->update();
	ERRCHECK(result);
}

/// <summary>
/// Para crear emisores
/// </summary>
/// <param name="position"> Necesita un Vector3 de su posicion </param>
/// <returns></returns>
SoundSystem::EmitterData* SoundSystem::createEmitter(const Vector3* position)
{
	SoundSystem::EmitterData* data = new SoundSystem::EmitterData(position);
	emitters.push_back(data);
	return data;
}

/// <summary>
/// Crea el listener 
/// </summary>
/// <param name="position"> Necesita ubicancia </param>
/// <param name="quaternion"> Necesita orientacion </param>
/// <returns></returns>
SoundSystem::ListenerData* SoundSystem::createListener(const Vector3* position, const Vector4* quaternion)
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
/// Util para transformaciones de Fmod
/// </summary>
/// <param name="in"></param>
/// <returns></returns>
FMOD_VECTOR SoundSystem::vecToFMOD(const Vector3& in)
{
	FMOD_VECTOR result;
	result.x = in.x;
	result.y = in.y;
	result.z = in.z;

	return result;
}

/// <summary>
/// Util para el reverb de Fmod
/// </summary>
/// <returns></returns>
FMOD::Reverb3D* SoundSystem::createReverb()
{
	FMOD::Reverb3D* reverb;
	FMOD_RESULT result = system->createReverb3D(&reverb);
	ERRCHECK(result);
	return reverb;
}


void SoundSystem::ERRCHECK(FMOD_RESULT result) const
{
	if (result != FMOD_RESULT::FMOD_OK)
		LOG("%s", FMOD_ErrorString(result));
}

/// <summary>
/// Devuelve el sonido de efectos procedente de recursos
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
Sound* SoundSystem::getSound(const std::string& name) const
{
	Sound* sound = ResourcesManager::getSound(name);
	if (sound == nullptr) return nullptr;

	// Wait till loaded
	FMOD_OPENSTATE state;
	FMOD_RESULT result;
	do {
		result = sound->getOpenState(&state, nullptr, nullptr, nullptr);
	} while (state == FMOD_OPENSTATE_LOADING);

	if (result != FMOD_OK) {
		LOG("SOUND MANAGER: Error playing sound %s", name.c_str());
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
	channel = nullptr;
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
/// Metodo que pone en pausa a todos los emisores?
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