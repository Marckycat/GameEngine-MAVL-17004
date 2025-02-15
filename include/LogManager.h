#pragma once
#include <iostream>

//Macros para facilitar el uso del LogManager, inspirados en Unreal y Android
//Log a secas, siempre es para debug y necesita tag
#define LOG(message, tag) LogManager::GetInstance()->Log(LogManager::DEBUG, message, tag)
//Log de error
#define LOGE(message, tag) LogManager::GetInstance()->Log(LogManager::LOG_ERROR, message, tag)
//Log de advertencia
#define LOGW(message, tag) LogManager::GetInstance()->Log(LogManager::LOG_WARNING, message, tag)
//Log informatibo
#define LOGI(message,tag) LogManager::GetInstance()->Log(LogManager::LOG_INFO, message, tag)
//Log verboso
#define LOGV(message, tag) LogManager::GetInstance()->Log(LogManager::LOG_VERBOSE, message, tag)
//Log para flojos
#define LOGD(message) LogManager::GetInstance()->Log(LogManager::LOG_DEBUG, message, "DEBUG")


class LogManager
{
public:
	static LogManager* GetInstance();

	enum ELogLevel
	{
		LOG_ERROR,
		LOG_WARNING,
		LOG_INFO,
		LOG_DEBUG,
		LOG_VERBOSE
	};
	ELogLevel logLevel = LOG_INFO;

	void Log(const char* message);
	void Log(ELogLevel level, const char* message);
	void Log(ELogLevel level, const char* message, const char* tag) const;

private:
	static LogManager* instance;
	LogManager();
	~LogManager();
	LogManager(const LogManager& other) = delete;
	LogManager& operator=(const LogManager& other) = delete;
	void init();
};

