# memalloc

A minimal, educational C++ memory allocator built on top of `sbrk`.

`memalloc` provides a small `malloc`-like API for allocating and freeing memory from a custom heap. It is intended for learning about allocator design, block metadata, free lists, and low-level memory management. It is **not** a production-ready replacement for `malloc`/`free`.

## Features

- Simple `malloc`-style API: `memalloc`, `memfree`
- First-fit search over a linked list of blocks
- Block metadata stored in a `BlockHeader`
- Heap growth via `sbrk`
- Tail-block shrinking when freeing the most recent allocation
- Alignment based on `alignof(std::max_align_t)`
- Small, readable C++ implementation

## Repository Layout

    .
    ├── include/
    │   └── memalloc.hpp
    └── src/
        ├── main.cpp
        └── memalloc.cpp

## API

    void* memalloc(std::size_t requestedSize);
    void  memfree(void* ptr);
    void* memcalloc(std::size_t num, std::size_t size);
    void* memrealloc(void* ptr, std::size_t size);

> **Note:** `memcalloc` and `memrealloc` are declared in the header but are not implemented yet. Only `memalloc` and `memfree` are currently available.

## Build and Run

Requires a POSIX-like environment with `sbrk` available, such as Linux or macOS.

    g++ -std=c++17 -Wall -Wextra -Iinclude src/memalloc.cpp src/main.cpp -o memalloc_demo
    ./memalloc_demo

## How It Works

### Block Metadata

Each allocation is preceded by a `BlockHeader`:

    struct alignas(alignment) BlockHeader
    {
        std::size_t size;
        bool isFree;
        BlockHeader* next;
    };

The header stores the requested user size, whether the block is free, and a pointer to the next block in the global list.

### Allocation

`memalloc`:

1. Returns `nullptr` if the requested size is zero.
2. Searches for the first free block large enough for the request.
3. If a suitable free block is found, marks it as used and returns the memory after the header.
4. Otherwise, requests `sizeof(BlockHeader) + requestedSize` bytes from the OS using `sbrk`.
5. Initializes the new block header, appends it to the global block list, and returns the user-accessible region.

### Freeing

`memfree`:

1. Returns immediately if `ptr` is `nullptr`.
2. Locates the `BlockHeader` immediately before the user pointer.
3. If the block is not the tail block, marks it as free.
4. If the block is the tail block, removes it from the block list and shrinks the heap with `sbrk`.
5. If it was the only block, resets the global `head` and `tail` pointers.

### Alignment

The allocator uses:

    constexpr std::size_t alignment = alignof(std::max_align_t);

`BlockHeader` is aligned to `std::max_align_t`, so the user pointer returned by `header + 1` is suitably aligned for standard types.

## Limitations

This allocator is intentionally simple and has several important limitations:

- No coalescing of adjacent free blocks.
- No splitting of larger free blocks to satisfy smaller requests.
- No thread safety.
- No double-free detection.
- `memcalloc` and `memrealloc` are declared but not implemented.
- Only the tail block is returned to the OS; interior free blocks remain in the heap.
- Assumes valid pointers are passed to `memfree`.
- Not a drop-in replacement for `malloc`/`free` in real applications.

## Future Improvements

Possible next steps for the project:

- Implement `memcalloc` and `memrealloc`.
- Split blocks when a free block is larger than the request.
- Coalesce adjacent free blocks.
- Add a best-fit or segregated free-list strategy.
- Add assertions and debug checks for invalid frees and corruption.
- Add unit tests and benchmarks.
- Add optional thread safety.
- Replace `sbrk` with `mmap` for more modern heap management.

## License

No license has been specified for this repository. If you intend for others to use, modify, or distribute this code, add a `LICENSE` file.
