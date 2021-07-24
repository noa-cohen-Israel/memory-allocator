#include "mallocAllocate.h"
#include <stdio.h>
struct MemoryAllocator MemoryAllocator;
struct MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size){
    unsigned char* m_memoryPool=(unsigned char*)memoryPool;
    for (int i=0;i<size;i++){
        m_memoryPool[i]=(unsigned char)0;
    }
    m_memoryPool[1]=(unsigned char)254;
    MemoryAllocator.pointer=(void*)m_memoryPool;
    MemoryAllocator.size=size;
    return &MemoryAllocator;
}

void* MemoryAllocator_release(struct MemoryAllocator* allocator){
    unsigned char * m_memoryPool=(unsigned char*)allocator->pointer;
    for (int i=0;i<allocator->size ;i++){
        m_memoryPool[i]=(unsigned char)0;
    }
    m_memoryPool[1]=(unsigned char)254;
    return allocator->pointer;
}
void* MemoryAllocator_allocate(struct MemoryAllocator* allocator,size_t size){
    size_t index=0;
    unsigned char * array=(unsigned char *)allocator->pointer;
    if( size%8>0){
    size=((size/8)+1)*8;}
    while (allocator->size>index+1){
        if ((int)array[index]==0){
            size_t current_size=(size_t)array[index+1];
            size_t next_size=(size_t)array[index+4+current_size];
            if (size<=(size_t)array[index+1]){
                array[index]=(unsigned char )1;
                array[index+1]=(unsigned char )size;
                unsigned char * block=array+index+2;
                size_t start_block=index + size+2;
                if (current_size-size>0) {
                    if ((size_t)index+3+current_size>=allocator->size || (int)array[index+3+current_size]==0){
                    array[start_block] = (unsigned char) 0;
                    array[start_block+1] = (unsigned char) (current_size - size-2);
                }
                }
                return (void *)block;

            }

        }
        index+=array[index+1]+2;
    }
    return (void *)NULL;
}

void MemoryAllocator_free(struct MemoryAllocator* allocator, void* ptr){
    unsigned char * array=(unsigned char *)ptr;
    (array-2)[0]=(unsigned char )0;

    size_t new_size=*(array-1);
    size_t index=new_size-1;
    while (allocator->size>index+1+ptr-allocator->pointer&& (int)array[index+1]==0){
        new_size+=array[index+2]+2;
        index+=array[index+2]+2;
    }
    (array-1)[0]=(unsigned char )new_size;

    return;


}
size_t MemoryAllocator_optimize(struct MemoryAllocator* allocator){
    unsigned char * array=(unsigned char *)allocator->pointer;
    size_t index=0;
    size_t size=0;
    while (allocator->size>index+1) {
        if ((int)array[index]==0){
            size_t start_index=index+1;
            size_t new_size=array[index+1];
            index+=new_size+2;
            while (allocator->size>index+1 && (int)array[index]==0){
                new_size+=array[index+1]+2;
                index+=array[index+1]+2;

            }
            size+=new_size;
            array[start_index]=(unsigned char )new_size;
        }
        index+=array[index+1]+2;

    }
    return size;
}

