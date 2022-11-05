#include <stdint.h>

#include "utils.h"
#include "printf.h"

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

uint64_t round_down(uint64_t in, uint64_t b) {
	int i;
	for (i = 0; !(b & 1); i++) { b >>= 1; }
	return (in >> i) << i; 
}

uint64_t round_up(uint64_t in, uint64_t n) {
	uint64_t rd = round_down(in, n);
	return (rd == in) ? in : rd + n;
}
