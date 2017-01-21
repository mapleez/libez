#include "ez.h"
#include "ez_strutils.h"
#include <string.h>
#include <stdlib.h>
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

char* str2lower (char* str) {
	char* p = str;
	if (! p) return NULL;

	while (*p) {
		*p = tolower (*p);
		p ++;
	}

	return str;
}

char* str2upper (char* str) {
	char* p = str;
	if (! p) return NULL;

	while (*p) { 
		*p = toupper (*p);
		p ++;
	}

	return str;
}

int main (int argc, char* argv []) {
	// char* str = strdup ("ok this is a string 12343,.//`.");
	// char* p = NULL;
	if (argc <= 1) {
		println ("No arguments");
		return 0;
	}

	// p = str2lower (str);
	// printf ("lower = %s\n", p);

	// p = str2upper (str);
	// printf ("upper = %s\n", p);

	// free (str);

	while (argc -- > 1) {
		// char* s = strdup (argv [argc]);

		printf ("Upper : %s\n", str2upper (argv [argc]));
		printf ("Upper : %s\n", str2lower (argv [argc]));

		// printf ("Upper : %s\n"
		// 				"Lower : %s\n",
		// 	str2upper (argv [argc]),
		// 	str2lower (argv [argc]));
		println ("");
	}

	return 0;
}

