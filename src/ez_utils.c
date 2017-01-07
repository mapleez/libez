#include <unistd.h>
#include "ez_utils.h"
#include <stdlib.h>
#include <fcntl.h>

void ez_daemonize (void) {
	int nullfd;

	if (fork () != 0)
		exit (0); /* parent exits */

	setsid (); /* Create a new session. */

	/* child process. */
	if ((nullfd = open ("/dev/null", O_RDWR, 0)) != -1) {
		dup2 (nullfd, STDIN_FILENO);
		dup2 (nullfd, STDOUT_FILENO);
		dup2 (nullfd, STDERR_FILENO);
		if (nullfd > STDERR_FILENO) 
			close (nullfd);
		// return RTNVAL_SUCC;
	}

	// return RTNVAL_FAIL;
}

// int _ez_daemonize (int out, int err) {
// }

/*
 * This function only calls the API daemon and 
 * return whether it's successful.
 * Return: RTNVAL_SUCC or  RTNVAL_FAIL
 *
 * Note: Redirect stdout, stderr to /dev/null
 *  and left the current direction unchanged.
 */
int ez_daemon () {
	int res = daemon (1, 0);
	return res == 0 ? RTNVAL_SUCC :RTNVAL_FAIL;
}


