#include <iostream>
#include "memalloc.hpp"
int main()
{
	void* p = memalloc(64);

	memfree(p);

	void* q = memalloc(64);

	std::cout << p << std::endl;
	std::cout << q  << std::endl;
	
	return 0;
}

