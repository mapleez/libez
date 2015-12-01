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

typedef char* (*fname_build) ();

typedef struct _ez_logger {
	int _type;
	FILE* _fstream;
	fname_build _nm_build;

} ez_logger,
	* pez_logger;


extern pez_logger ez_logger_new (fname_build);

extern void ez_logger_despose (pez_logger);

// log with string
extern bool ez_logger_log (pez_logger, const char*);

// log with format string
extern bool ez_logger_logf (pez_logger, const char*, const char*, ...);

#ifdef __cplusplus
}
#endif

#endif // ~ _EZ_LOG_H_

