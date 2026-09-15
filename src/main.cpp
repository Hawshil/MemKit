#include <iostream>
#include "memalloc.hpp"
int main()
{
	void* p = memalloc(32);
	std::cout << p << std::endl;

	return 0;
}

