
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc/malloc.h> // for malloc_printf()

#define INTERPOSE(_replacement, _replacee) __attribute((used)) static struct { const void* replacement; const void* replacee; } _interpose_##_replacee __attribute__ ((section("__DATA, __interpose"))) = { (const void*) (unsigned long) &_replacement, (const void*) (unsigned long) &_replacee };

void *my_malloc (int size)
{
    // In our function we have access to the real malloc() -
    // and since we don't want to mess with the heap ourselves,
    // just call it.
    void *returned = malloc(size);
    // call malloc_printf() because the real printf() calls malloc()
    // internally - and would end up calling us, recursing ad infinitum
    malloc_printf("+ %p %d\n",returned, size);
    return (returned);
}

void my_free (void *freed)
{
    // Free - just print the address, then call the real free()
    malloc_printf("- %p\n", freed);
    free(freed);
}

INTERPOSE(my_free,free);
INTERPOSE(my_malloc,malloc);
