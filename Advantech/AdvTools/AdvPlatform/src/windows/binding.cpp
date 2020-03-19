#include "binding.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

ssize_t ADVPLAT_CALL getline(char **lineptr, size_t *n, void *stream) {
	std::filebuf buf((FILE *)stream);
	std::istream base(&buf);
	std::string sbuf;
	char* point = *lineptr;
	if (!base.good()) return -1;
	if (feof((FILE *)stream)) return -1;

	std::getline(base, sbuf);
	*n = sbuf.size() + 1;

	if (point != NULL) {
		point = (char*)realloc(point, *n);
	} 
	else point = (char*)malloc(*n);
	if(point == NULL) return -1;
	strncpy(point, sbuf.c_str(), *n);
	*lineptr = point;
	return *n;
}

