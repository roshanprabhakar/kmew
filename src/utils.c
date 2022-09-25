#include <stdint.h>

#include "utils.h"

void* memset(void* data, int c, uint32_t len) {
  for (char* i = (char*) data; i < (char*) data + len; i++) 
    *i = (unsigned char) c;
  return data;
}

int32_t strcmp(char const* str1, char const* str2) {
	int i = 0, diff, sum;
	for (;; i++) {

		diff = str1[i] - str2[i];
		sum = str1[i] + str2[i];

		if (sum == 0) 			break;
		else if (diff != 0) return diff;
	}
	return 0;
}
