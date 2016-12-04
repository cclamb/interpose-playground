#include <stdio.h>
#include <dlfcn.h>        // for dladdr(3)
#include <mach-o/dyld.h>  // for _dyld_ functions

#include "printer.h"

void list_images(void) {
        // List all mach-o images in a process
        uint32_t i;
        uint32_t ic = _dyld_image_count();
        printf ("Got %d images\n",ic);
        for (i = 0; i < ic; i++)
        {
          printf ("%d: %p\t%s\n", 
                  i, 
                  _dyld_get_image_header(i), 
                  _dyld_get_image_name(i));
        }
}

int main() {
  list_images();
  print_hello();
  print_message("...Gooodbye!\n");
  return 0;
}
