#include <stdint.h>

#include "utils.h"

void* memset(void* data, int c, uint32_t len) {
  for (char* i = (char*) data; i < (char*) data + len; i++) 
    *i = (unsigned char) c;
  return data;
}
