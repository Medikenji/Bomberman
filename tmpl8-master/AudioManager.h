#pragma once
#include "EntityContainer.h"
#include "miniaudio.h"

enum Audio {
	MenuSong = 0,
	MenuSelect = 1,
	MainTheme = 2,
	BombExplode = 3,
	DeathSound = 4
};

class AudioManager
{
public:
	static AudioManager* GetAudioManager();
	static void DestroyAudioManager();
	static void PlayAudio(UINT8 _audio);
	static void StopAudio(UINT8 _audio);
	static void StopAll();

private:
	AudioManager();
	~AudioManager();
	void InitFromFile(const char* _filePath, ma_sound& _sound);
	inline static AudioManager* _instance = nullptr;
	inline static ma_engine m_engine;
	inline static ma_result result;

	// Audios
	inline static ma_sound m_menuSong;
	inline static ma_sound m_menuSelect;
	inline static ma_sound m_mainTheme;
	inline static ma_sound m_bombExplosion;
	inline static ma_sound m_deathSound;
};

