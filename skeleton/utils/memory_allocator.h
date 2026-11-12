#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <memoryapi.h>

namespace mem_alloc {
	void* heap_alloc(size_t bytes) {
		return VirtualAlloc(NULL, bytes, MEM_COMMIT, PAGE_READWRITE);
	}
}

#endif