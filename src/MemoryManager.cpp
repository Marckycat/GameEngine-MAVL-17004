#include "MemoryManager.h"
#include <iostream>

MemoryManager* MemoryManager::instance = nullptr;

MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
}

void MemoryManager::init()
{
	std::cout << "MemoryManager::init()" << std::endl;
}

MemoryManager* MemoryManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MemoryManager();
		instance->init();
	}
	return instance;
}

size_t MemoryManager::alloc(size_t size)
{
	std::cout << "Allocating " << size << " bytes" << std::endl;
	void* ptr = malloc(size);
	return size;
}

void MemoryManager::free(void* ptr)
{
}
