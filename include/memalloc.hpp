#ifndef MEMALLOC_HPP
#define MEMALLOC_HPP

#include <cstddef>

constexpr std::size_t alignment = alignof(std::max_align_t);

struct alignas(alignment) BlockHeader
{
	std::size_t size;
	bool isFree;
	BlockHeader* next;
};

void* 	memalloc (std::size_t RequestedSize);
void 	memfree	(void* ptr);
void* 	memcalloc (std::size_t num, std::size_t size);
void* 	memrealloc (void* ptr, std::size_t size);

#endif
