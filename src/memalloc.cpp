#include "memalloc.hpp"
#include <unistd.h>

static BlockHeader* head = nullptr;

void* memalloc(std::size_t RequestedSize)
{
	// allocate space for both metadata and the user requested size
	std::size_t totalSize = RequestedSize + sizeof(BlockHeader);
	BlockHeader* header = static_cast<BlockHeader*>(sbrk(totalSize));

	// sbrk returns (void*)-1 on failure
	if(header == reinterpret_cast<BlockHeader*>((BlockHeader*)-1))
	{
		return nullptr;
	}

	header->size = RequestedSize;
	header->isFree = false;

	// return the memory immediately after the metadata (block header)
	return header + 1;
}


