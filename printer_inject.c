#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define OK    1
#define FAIL  0

int print_message(const char* msg);
int print_hello(void);

typedef struct interpose {
  void *new;
  void *old;
} interpose_t;

int new_print_message(const char* msg);
int new_print_hello(void);

static const interpose_t injected_functions[] __attribute__((section("__DATA, __interpose"))) = {
  { (void*) new_print_message, (void*) print_message },
  { (void*) new_print_hello, (void*) print_hello }
};

int new_print_message(const char* msg) {
  char* buffer = (char*) malloc(11 + sizeof(msg));
  snprintf(buffer, 10, "message: %s\n", msg);
  print_message(buffer);
  free(buffer);
  return OK;
}

int new_print_hello(void) {
  printf("Hola!\n");
  return OK;
}
