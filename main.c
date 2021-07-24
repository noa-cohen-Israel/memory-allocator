#include <stdio.h>
#include <stddef.h>
#include "mallocAllocate.h"
int main() {
    unsigned char memoryPool[256];
    struct MemoryAllocator* a;
    a=MemoryAllocator_init(memoryPool,(size_t)256);
    unsigned char* n=(unsigned char*)a->pointer;
    void * p1=MemoryAllocator_allocate(a,(size_t)4);
    void * p2=MemoryAllocator_allocate(a,(size_t)4);
    void * p3=MemoryAllocator_allocate(a,(size_t)4);

    MemoryAllocator_free(a,p2);
    void * p4=MemoryAllocator_allocate(a,(size_t)9);
    MemoryAllocator_free(a,p3);
//    MemoryAllocator_free(a,p1);
    MemoryAllocator_free(a,p4);
    size_t size=MemoryAllocator_optimize(a);
    printf("size: %zu",size);
    a=MemoryAllocator_release(a);

    return 0;
};