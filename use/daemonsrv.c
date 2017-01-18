#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ez.h"


void daemonize(void) {
    int fd;

    if (fork() > 0) exit(0); /* parent exits */
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but
     * the 'logfile' is set to 'stdout' in the configuration file
     * it will not log at all. */
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
}


int main (int argc, char* argv []) {
	
	// ez_daemonize ();
	daemonize ();

	while (1) {
		printf ("%lld\n", (long long int) time (NULL));
		sleep (1);
	}

	return 0;
}

