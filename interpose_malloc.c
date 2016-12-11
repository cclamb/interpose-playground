
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc/malloc.h>

#define INTERPOSE(_replacement, _replacee) \
    __attribute__((used)) static struct { \
        const void* replacement; \
        const void* replacee; \
    } _interpose_##_replacee __attribute__ ((section("__DATA, __interpose"))) = { \
        (const void*) (unsigned long) &_replacement, \
        (const void*) (unsigned long) &_replacee \
    };

void *my_malloc (int size)
{
    void *returned = malloc(size);
    malloc_printf("[+] %p %d\n",returned, size);
    return (returned);
}

void my_free (void *freed)
{
    malloc_printf("[-] %p\n", freed);
    free(freed);
}

INTERPOSE(my_free,free);
INTERPOSE(my_malloc,malloc);
