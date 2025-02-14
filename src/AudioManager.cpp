#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

AudioManager* AudioManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new AudioManager();
		instance->init();
	}
	return instance;
}

void AudioManager::init()
{
	//Inicializar el sistema de audio de raylib
	InitAudioDevice();
}

void AudioManager::LoadBackgroundMusic(const char* filename)
{
	backgroundMusic = LoadMusicStream(filename);
}

void AudioManager::PlayBGM()
{
	PlayMusicStream(backgroundMusic);
}

void AudioManager::Update()
{
	UpdateMusicStream(backgroundMusic);
}
