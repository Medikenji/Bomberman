#include "precomp.h"
#include "AudioManager.h"
#define MINIAUDIO_IMPLEMENTATION
//#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
//#define MA_ENABLE_DSOUND

#include "../lib/miniaudio.h"	// miniaudio is an audio playback and capture library for C and C++. It's made up of a single source file, has no external dependencies and is released into the public domain.


AudioManager* AudioManager::GetAudioManager()
{
	if (_instance)
	{
		return _instance;
	}
	_instance = new AudioManager();
	return _instance;
}


void AudioManager::DestroyAudioManager()
{
	delete GetAudioManager();
}


void AudioManager::PlayAudio(uint_fast8_t _audio)
{
	switch (_audio)
	{
	case Audio::MenuSong:
		ma_sound_start(&m_menuSong);
		break;
	case Audio::MenuSelect:
		ma_sound_start(&m_menuSelect);
		break;
	case Audio::MainTheme:
		ma_sound_start(&m_mainTheme);
		break;
	case Audio::BombExplode:
		ma_sound_start(&m_bombExplosion);
		break;
	case Audio::DeathSound:
		ma_sound_start(&m_deathSound);
		break;
	case Audio::VictoryTheme:
		ma_sound_start(&m_victoryTheme);
		break;
	default:
		FatalError("Audio does not exist");
		break;
	}
}


void AudioManager::StopAudio(uint_fast8_t _audio)
{
	switch (_audio)
	{
	case Audio::MenuSong:
		ma_sound_set_at_end(&m_menuSong, MA_TRUE);
		ma_sound_stop(&m_menuSong);
		break;
	case Audio::MenuSelect:
		ma_sound_set_at_end(&m_menuSelect, MA_TRUE);
		ma_sound_stop(&m_menuSelect);
		break;
	case Audio::MainTheme:
		ma_sound_set_at_end(&m_mainTheme, MA_TRUE);
		ma_sound_stop(&m_mainTheme);
		break;
	case Audio::BombExplode:
		ma_sound_set_at_end(&m_bombExplosion, MA_TRUE);
		ma_sound_stop(&m_bombExplosion);
		break;
	case Audio::DeathSound:
		ma_sound_set_at_end(&m_deathSound, MA_TRUE);
		ma_sound_stop(&m_deathSound);
		break;
	case Audio::VictoryTheme:
		ma_sound_set_at_end(&m_victoryTheme, MA_TRUE);
		ma_sound_stop(&m_victoryTheme);
		break;
	default:
		FatalError("Audio does not exist");
		break;
	}
}


void AudioManager::StopAll()
{
	StopAudio(Audio::MenuSong);
	StopAudio(Audio::MenuSelect);
	StopAudio(Audio::MainTheme);
	StopAudio(Audio::BombExplode);
	StopAudio(Audio::DeathSound);
	StopAudio(Audio::VictoryTheme);
}


AudioManager::AudioManager()
{
	ma_engine_init(NULL, &m_engine);
	srand((unsigned int)time(0));
	// Init MenuTheme
	if (!(rand() % 100))
	{
		InitFromFile("assets/audio/BomberManMenuTheme.mp3", m_menuSong);
	}
	else
	{
		InitFromFile("assets/audio/BomberManMenuThemeBit.mp3", m_menuSong);
	}
	ma_sound_set_looping(&m_menuSong, true);
	ma_sound_set_start_time_in_milliseconds(&m_menuSong, 50);

	// Init MenuSelect
	InitFromFile("assets/audio/MenuSelect.mp3", m_menuSelect);
	ma_sound_set_volume(&m_menuSelect, 0.8f);

	// Init MainTheme
	InitFromFile("assets/audio/BomberManTheme.mp3", m_mainTheme);
	ma_sound_set_looping(&m_mainTheme, true);

	// Init BombExplosion
	InitFromFile("assets/audio/BombExplosion.mp3", m_bombExplosion);

	// Init DeathSound
	InitFromFile("assets/audio/DeathSound.mp3", m_deathSound);

	// Init VictoryTheme
	if (!(rand() % 2))
	{
		InitFromFile("assets/audio/VictoryI.mp3", m_victoryTheme);
	}
	else
	{
		InitFromFile("assets/audio/VictoryII.mp3", m_victoryTheme);
	}
		ma_sound_set_looping(&m_victoryTheme, true);
}


AudioManager::~AudioManager()
{
	ma_sound_uninit(&m_menuSong);
	ma_sound_uninit(&m_menuSelect);
	ma_sound_uninit(&m_mainTheme);
	ma_sound_uninit(&m_bombExplosion);
	ma_sound_uninit(&m_deathSound);
	ma_sound_uninit(&m_victoryTheme);
	ma_engine_uninit(&m_engine);
}


void AudioManager::InitFromFile(const char* _filePath, ma_sound& _sound)
{
	result = ma_sound_init_from_file(&m_engine, _filePath, 0, NULL, NULL, &_sound);
	if (result != MA_SUCCESS) {
		FatalError(_filePath);
	}
}