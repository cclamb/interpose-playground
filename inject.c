#include <stdio.h>
#include <stddef.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define OK    1
#define FAIL  0

unsigned char print_message(const char* msg) {
  char* buffer = (char*) malloc(11 + sizeof(msg));
  //snprintf(buffer, 10, "message: %s\n", msg);
  //((int (*)(const char*)) dlsym(RTLD_NEXT, "print_message"))("foobar");//print_message(buffer);
  unsigned char (*original)(const char*) = dlsym(RTLD_DEFAULT, "print_hello");
  printf("error: %s\n", dlerror());
  original("message");
  free(buffer);
  return OK;
}

unsigned char print_hello(void) {
  printf("Hola!\n");
  return OK;
}
