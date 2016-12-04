#include <stdio.h>
#include "printer.h"

error_t print_message(const char* msg) {
  printf("%s\n", msg);
  return OK;
}

error_t print_hello(void) {
  printf("Hello!\n");
  return OK;
}
