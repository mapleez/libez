#include <unistd.h>
#include "ez_utils.h"
#include <stdio.h>

int main (int argc, char* argv []) {
	int i = 0;
	/* int res = */ez_daemonize ();
	FILE* fd = fopen ("./output", "a+");

	if (fd == NULL) {
		printf ("Error open output");
		return 0;
	}

	for (; i < 10000; i ++) {
		printf ("Error %d\n", i);
		fwrite ("ferror\n", 7, 1, fd);
		fflush (fd);
		sleep (1);
	}

	return 0;
}

