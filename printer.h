#ifndef __PRINTER_H__
#define __PRINTER_H__

#define OK    1
#define FAIL  0

typedef unsigned char error_t;

error_t print_message(const char* msg);
error_t print_hello(void);

#endif
