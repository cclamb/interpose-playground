#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>


#define DYLD_INTERPOSE(_replacment,_replacee) \
__attribute__((used)) static struct{ const void* replacment; const void* replacee; } _interpose_##_replacee \
__attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacment, (const void*)(unsigned long)&_replacee };


void* pMalloc(size_t size) //would be nice if I didn't have to rename my function..
{
    printf("Allocated: %zu\n", size);
    return malloc(size);
}

DYLD_INTERPOSE(pMalloc, malloc);
