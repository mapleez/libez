#include "ez_utils.h"
#include <unistd.h>
#include <stdlib.h>

int ez_daemonize () {
	int pid = fork ();
	if (pid == -1) return RTNVAL_ERR;
	else if (pid) exit (0);
	if (setsid () == -1) 
		return RTNVAL_FAIL;
	// TODO... redirect file handler.
	return RTNVAL_SUCC;
}

