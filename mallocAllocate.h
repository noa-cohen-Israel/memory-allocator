//
// Created by bootcamp on 21/07/2021.
//
#include <stddef.h>
#ifndef UNTITLED1_MALLOCALLOCATE_H
#define UNTITLED1_MALLOCALLOCATE_H
struct MemoryAllocator{
void* pointer;
size_t size;
};

///* memoryPool is a ptr to an already-existing large memory block */
struct MemoryAllocator* MemoryAllocator_init(void* memoryPool,
                                             size_t size);
///* Returns a ptr to the memoryPool */
void* MemoryAllocator_release(struct MemoryAllocator* allocator);
void* MemoryAllocator_allocate(struct MemoryAllocator* allocator,
                               size_t size);
///* Merge the next adjacent block is free */
void MemoryAllocator_free(struct MemoryAllocator* allocator, void*
ptr);
///* Merges all adjacent free blocks, and returns the size of largest free block */
size_t MemoryAllocator_optimize(struct MemoryAllocator* allocator);
#endif //UNTITLED1_MALLOCALLOCATE_H
