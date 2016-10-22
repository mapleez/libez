#include "ez_bytes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv []) {
	// test ez_bytes_index_sep ()
	char * s = "fds,dsf,fea,cxfda,fzfd,faffd,fd,sdfsd";
	char * sep = "f";

	{
		byte string [24]; // = malloc ()
		byte string1 [24];
		int len = ez_bytes_ull2string (327132, string);
		len = ez_bytes_ll2string (-7431412, string1);
		printf ("%s, %s\n", string, string1);
	}

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

	{
		char * _s = "fafnjnvajnvkajzhongfafnkvnajflejfzhong";
		bool flag = ez_bytes_hasprefix (_s, "zhong", strlen (_s),
				strlen ("zhong"));
		printf ("prefix %s  %s  flag= %d\n", _s, "zhong", flag);
		flag = ez_bytes_hassuffix (_s, "zhong", strlen (_s), strlen ("zhong"));
		printf ("suffix %s  %s  flag= %d\n", _s, "zhong", flag);
	}
	
	return 0;
}

