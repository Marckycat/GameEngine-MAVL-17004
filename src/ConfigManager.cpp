#include "ConfigManager.h"
#include "LogManager.h"
#include <fstream>
#include <string>

ConfigManager* ConfigManager::instance = nullptr;

ConfigManager* ConfigManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ConfigManager();
		instance->init();
	}
	return instance;
}

void ConfigManager::SetArguments(int argc, char** argv)
{
}

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::init()
{
	//valores default
	video.screenWidth = 640;
	video.screenHeight = 480;
	video.fullscreen = false;
	video.vsync = true;

	LOGI("Inicializando", "ConfigManager");
	std::ifstream file("config.ini");
	if (file.is_open())
	{
		//LOGI("Abriendo archivo de configuracion", "ConfigManager");
		std::string line;
		while (std::getline(file, line))
		{
			LOGD(line.c_str());
		}
	}
	else
	{
		LOGE("No se pudo abrir el archivo de configuracion", "ConfigManager");
	}
}
