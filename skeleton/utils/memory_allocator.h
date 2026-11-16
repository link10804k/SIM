#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <memoryapi.h>
#include <string>

namespace mem_alloc {
	void* heap_alloc(size_t bytes) {
		return VirtualAlloc(NULL, bytes, MEM_COMMIT, PAGE_READWRITE);
	}
	void heap_free(void* block) {
		if (VirtualFree(block, 0, MEM_RELEASE) == 0) {
			printf("Error code: %s\n", std::to_string(GetLastError()).c_str());
			exit(1);
		}
	}
}

#endif