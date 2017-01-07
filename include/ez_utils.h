#ifndef _EZ_UTILS_H_
#	define _EZ_UTILS_H_

#include "ez.h"

/* To fork a child process and
 * setsid it to a daemonize.
 * Return RTNVAL_SUCC if successful,
 * otherwize return RTNVAL_FAIL.
 * Return RTNVAL_ERR for error.
*/ 
extern void ez_daemonize (void);

/*
 * This function only calls the API daemon and 
 * return whether it's successful.
 * Return RTNVAL_SUCC or  RTNVAL_FAIL
 */
extern int ez_daemon ();

#endif // ~ _EZ_UTILS_H_
