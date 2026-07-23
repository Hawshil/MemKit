#ifndef MEMALLOC_HPP
#define MEMALLOC_HPP

#include <cstddef>

void* memalloc(std::size_t size);
void memfree(void* ptr);
void* memcalloc(std::size_t num, std::size_t size);
void* memrealloc(void* ptr, std::size_t size);

#endif
