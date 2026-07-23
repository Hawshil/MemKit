#include <iostream>
#include "memalloc.hpp"
#include <unistd.h>

void* memalloc(std::size_t size)
{
	std::cout << sbrk(0) << std::endl;
	sbrk(100);
	std::cout << sbrk(0) << std::endl;

	void* block = sbrk(size);

	if(block == (void*)-1)
	{
		return nullptr;
	}

	return block;
}


