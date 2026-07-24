#include <iostream>
#include "memalloc.hpp"
#include <unistd.h>

static BlockHeader* head = nullptr;
static BlockHeader* tail = nullptr;

void* memalloc(std::size_t RequestedSize)
{
	// allocate space for both metadata and the user requested size
	std::size_t totalSize = RequestedSize + sizeof(BlockHeader);
	BlockHeader* header = static_cast<BlockHeader*>(sbrk(totalSize));

	// sbrk returns (void*)-1 on failure
	if(header == reinterpret_cast<BlockHeader*>(-1))
	{
		return nullptr;
	}

	header->size = RequestedSize;
	header->isFree = false;
	header->next = nullptr;

	if(head == nullptr)
	{
		head = header;
	}
	if(tail != nullptr)
	{
		tail->next = header;
	}
	
	tail = header;
	
	// return the memory immediately after the metadata (block header)
	return header + 1;
}
