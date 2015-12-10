#ifndef _EZ_LOG_H_
#	define _EZ_LOG_H_

/*
 * Author : ez
 * Date : 2015/12/1
 * Describe : Define a simple Logger and its interfaces.
 *
*/

#include "ez.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// static log type
#	define LOGTYPE_DEFAULT    2
#	define LOGTYPE_USER       4 

#	define SIZE_LOGGER   (sizeof (ez_logger))

#	define FILE_EXISTS(___FNAME)			(access ((___FNAME), F_OK) == 0)
#	define FILE_READABLE(___FNAME)  	(access ((___FNAME), R_OK) == 0)
#	define FILE_WRITABLE(___FNAME)  	(access ((___FNAME), W_OK) == 0)
#	define FILE_EXECUTABLE(___FNAME)  (access ((___FNAME), X_OK) == 0)
#	define FILE_RDWT(___FNAME)   (access ((___FNAME), R_OK | W_OK) == 0)
#	define FILE_RDWTX(___FNAME)     \
	(access ((___FNAME), R_OK | W_OK | X_OK) == 0)

typedef char* (*fname_build) ();

typedef struct _ez_logger {
	int _type;
	FILE* _fstream;
	fname_build _nm_build;

} ez_logger,
	* pez_logger;


// create a new logger
extern pez_logger ez_logger_new (fname_build);

// dispose the logger
extern void ez_logger_despose (pez_logger*);

// log with string
extern bool ez_logger_log (pez_logger, const char*);

// this function will add timestamp automatically
extern bool ez_logger_logln (pez_logger, const char*);

// log with format string
extern bool ez_logger_logf (pez_logger, const char*, ...);

#ifdef __cplusplus
}
#endif

#endif // ~ _EZ_LOG_H_

