#include "precomp.h"
#include "AudioManager.h"
#define MINIAUDIO_IMPLEMENTATION
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


void AudioManager::PlayAudio(UINT8 _audio)
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
	default:
		FatalError("Audio does not exist");
		break;
	}
}


void AudioManager::StopAudio(UINT8 _audio)
{
	switch (_audio)
	{
	case Audio::MenuSong:
		ma_sound_stop(&m_menuSong);
		break;
	case Audio::MenuSelect:
		ma_sound_stop(&m_menuSelect);
		break;
	case Audio::MainTheme:
		ma_sound_stop(&m_mainTheme);
		break;
	case Audio::BombExplode:
		ma_sound_stop(&m_bombExplosion);
		break;
	case Audio::DeathSound:
		ma_sound_start(&m_deathSound);
		break;
	default:
		FatalError("Audio does not exist");
		break;
	}
}


void AudioManager::StopAll()
{
	ma_sound_stop(&m_menuSong);
	ma_sound_stop(&m_menuSelect);
	ma_sound_stop(&m_mainTheme);
	ma_sound_stop(&m_bombExplosion);
	ma_sound_start(&m_deathSound);
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
	ma_sound_start(&m_menuSong);

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
}


AudioManager::~AudioManager()
{
	ma_engine_uninit(&m_engine);
	ma_sound_uninit(&m_menuSong);
	ma_sound_uninit(&m_menuSelect);
	ma_sound_uninit(&m_mainTheme);
	ma_sound_uninit(&m_bombExplosion);
	ma_sound_uninit(&m_deathSound);
}

void AudioManager::InitFromFile(const char* _filePath, ma_sound& _sound)
{
	result = ma_sound_init_from_file(&m_engine, _filePath, 0, NULL, NULL, &_sound);
	if (result != MA_SUCCESS) {
		FatalError(_filePath);
	}
}