#pragma once
#include <iostream>

class MemoryManager
{
	//Hay que crearlo como singleton	
public:
	static MemoryManager* getInstance();

	size_t alloc(size_t size);
	void free(void* ptr);

private:
	static MemoryManager* instance;
	//Evitar que se pueda copiar
	MemoryManager(const MemoryManager&) = delete;
	MemoryManager& operator=(const MemoryManager&) = delete;
	MemoryManager();
	~MemoryManager();

	void init();
};

