#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "ez.h"

int main (int argc, char* argv []) {
	
	ez_daemonize ();

	while (1) {
		printf ("%s", time (NULL));
		sleep (1);
	}

	return 0;
}

