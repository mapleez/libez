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
		char * _s = "fafnjnvajnvkajzhongfafnkvnajflejfzhong";
		int count = ez_bytes_count_bytes 
			(_s, "zhong", strlen (_s), strlen ("zhong"));
		printf ("%s  %s  count = %d\n", _s, "zhong", count);
	}
	return 0;
}

