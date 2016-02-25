#ifndef _EZ_UTILS_H_
#	define _EZ_UTILS_H_

#include "ez.h"

/* To fork a child process and
 * setsid it to a daemonize.
 * Return RTNVAL_SUCC if successful,
 * otherwize return RTNVAL_FAIL.
 * Return RTNVAL_ERR for error.
*/ 
extern int ez_daemonize ();

#endif // ~ _EZ_UTILS_H_
