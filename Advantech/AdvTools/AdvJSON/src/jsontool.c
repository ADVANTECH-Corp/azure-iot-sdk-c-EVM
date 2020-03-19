#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jsontool.h"
#include "platform.h"

/* Utility to jump whitespace and cr/lf */
char *skip(char *in) {
	while (in && *in && (unsigned char)*in<=32) {
		in++; 
	}
	return in;
}

void doubleQuote(char *target, const char *source, int *len) {
	target[0] = '\"';
	memcpy(target+1,source,*len);
	target[(*len)+1] = '\"';
	*len += 2;
	target[*len] = 0;
}

char *jmalloc(char *target, size_t*alloc, size_t len) {
	if(*alloc < len) {
		if(*alloc == 0) {
			target=(char *)malloc(len);
		} else {
			target=(char *)realloc(target,len);
		}
		*alloc = len;
	}
	else if (*alloc > len) {
		free(target);
		target = (char *)malloc(len);
		*alloc = len;
	}
	return target;
}

size_t selen(char* e, char* s) {
	return (size_t)e - (size_t)s;
}
