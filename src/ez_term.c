#include "ez_term.h"
#include <stdarg.h>

int ez_colorprintf (int _color, const char * _fmt, ...) {
	int fcolor = -1, retval = 0;
	va_list args;
	fcolor = _color + 1;
	if (fcolor && printf ("\033[1;3%dm", fcolor) < 0)	
		return retval;
	va_start (args, _fmt);
	if (! args) return retval;
	retval = vprintf (_fmt, args);
	va_end (args);
	if (fcolor && printf ("\033[0m") < 0)
		return 0;
	return retval;
}


