#include <stdlib.h>
#include <memory>
#include <iostream>

bool memoryAllocFail = false;

void* operator new(std::size_t size)
{
	if (memoryAllocFail)
	{
		throw std::bad_alloc();
	}

	return ::malloc(size);
	// void *Memory =  ::operator new (size);
	// return Memory;
}

void operator delete(void* block)
{
	::free(block);
}
