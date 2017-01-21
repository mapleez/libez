#include "ez_strutils.h"
#include <ctype.h>

char* skip_token (const char* p) {
	// while (isspace ((unsigned char) *p) ) ++ p;
	p = skip_whitespace (p);
	while (*p && ! isspace ((unsigned char) *p)) ++ p;
	return (char*) p;
}


char* skip_whitespace (const char* p) {
	while (isspace ((unsigned char) *p)) ++ p;
	return (char*) p;
}

