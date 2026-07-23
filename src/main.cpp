#include <iostream>
#include "memalloc.hpp"
int main()
{
	int* value = static_cast<int*>(memalloc(sizeof(int))); 
	*value = 43;
	std::cout << *value << std::endl;
	return 0;
}

