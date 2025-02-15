#include "LogManager.h"

LogManager* LogManager::instance = nullptr;

LogManager* LogManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new LogManager();
		instance->init();
	}
	return instance;
}

void LogManager::Log(const char* message)
{
	Log(LOG_INFO, message);
}

void LogManager::Log(ELogLevel level, const char* message)
{
	Log(level, message, "LOG");
}

void LogManager::Log(ELogLevel level, const char* message, const char* tag) const
{
	if (level <= logLevel) {
		std::cout << tag << ": " << message << std::endl;
	}
}

LogManager::LogManager()
{
}

LogManager::~LogManager()
{
}

void LogManager::init()
{
}
