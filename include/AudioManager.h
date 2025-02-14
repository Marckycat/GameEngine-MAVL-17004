#pragma once
#include "raylib.h"

class AudioManager
{

public:
	static AudioManager* getInstance();

	void init();
	Music backgroundMusic;
	void LoadBackgroundMusic(const char* filename);
	void PlayBGM();
	void Update();
	
private:
	static AudioManager* instance;
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager();
	~AudioManager();
};

