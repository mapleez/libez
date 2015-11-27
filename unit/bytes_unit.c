#include "ez_bytes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv []) {
	// test ez_bytes_index_sep ()
	char * s = "fds,dsf,fea,cxfda,fzfd,faffd,fd,sdfsd";
	char * sep = "f";
	{
		int index = ez_bytes_index_sep 
			((bytes)s, (bytes)sep, strlen (s), strlen (sep));
		printf ("%s  %s  index = %d\n", s, sep, index);
	}

	// test ez_bytes_count_bytes ()
	{
		// ERROR 11/27
		int count = ez_bytes_count_bytes 
			(s, sep, strlen (s), strlen (sep));
		printf ("%s  %s  count = %d\n", s, sep, count);
	}
	return 0;
}
