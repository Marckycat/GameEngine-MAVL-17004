#pragma once
#include <iostream>

class ConfigManager
{
public:
	static ConfigManager* GetInstance();
	void SetArguments(int argc, char** argv);

	struct EVideo {
		int screenWidth;
		int screenHeight;
		bool fullscreen;
		bool vsync;
	};
	EVideo GetVideo() const { return video; }

private:
	static ConfigManager* instance;
	ConfigManager();
	~ConfigManager();
	ConfigManager(const ConfigManager& other) = delete;
	ConfigManager& operator=(const ConfigManager& other) = delete;

	void init();
	EVideo video;
};

