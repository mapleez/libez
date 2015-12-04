#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// int printlnf (const char* fmt, ...) {
// 	va_list argptr;
// 	va_start (argptr, fmt);
// }

char* printlnf (const char* fmt, ...) {
	char* ptr = NULL;
	int done = 0;
	va_list args;
	ptr = (char*) calloc (20, 1);

	va_start (args, fmt);
	done = vsprintf (ptr, fmt, args);
	va_end (args);

	if (done) {
		printf ("%s\n", ptr);
		free (ptr);
		return ptr = NULL;
	} else {
		printf ("error\n");
		return ptr;
	}

}


int main (argc, argv)
	int argc;
	char* argv [];
{
	printf ("%d\n", printlnf ("%s %d", "the parameter is ", 20));
	return 0;
}

