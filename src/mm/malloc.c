// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	void *ptr; // pointer to the zone where we are going to allocate memory

	// search for an available memory zone with enough space
	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	// check if any available memory zone has been found
	if (ptr == MAP_FAILED)
		return NULL;

	/* link the new memory block to the list and check if
	the whole process was successful */
	if (mem_list_add(ptr, size) == -1)
		return NULL;

	// return pointer to the freshly allocated memory zone
	return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	// use the already implemented malloc function to allocate memory
	void *ptr;
	ptr = malloc(nmemb * size);

	// check if the allocation was successful
	if (!ptr)
		return NULL;

	// initialize the whole new block of memory with 0
	memset(ptr, 0, nmemb * size);

	return ptr;
}

void free(void *ptr)
{
	if (!ptr)
		return;

	//search for the block pointed to by ptr in the memory list
	struct mem_list *block;
	block = mem_list_find(ptr);

	// check if there was any block found in the memory list
	if (!block)
        return;

	// free the block's memory and check if the operation was successful
	if (munmap(block->start, block->len) == -1)
		return;

	/* take out the block from the memory list and take care of
	the links between the remaining blocks in the list */
	if (mem_list_del(block->start) == -1)
		return;
}

void *realloc(void *ptr, size_t size)
{
	// allocate a new block of memory with the new size
	void *new;
	new = malloc(size);

	// check if the allocation was successful
	if (!new)
		return NULL;

	// find the old size of the block
	struct mem_list *old_block;
	size_t old_size;
	old_block = mem_list_find(ptr);
	old_size = old_block->len;

	// move the info from the old block to the new block
	if (size > old_size)
		memcpy(new, ptr, old_size);
	else
		memcpy(new, ptr, size);

	// free the memory ocupied by the old memory block
	free(ptr);

	return new;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	void *new = realloc(ptr, nmemb * size);
	return new;
}
