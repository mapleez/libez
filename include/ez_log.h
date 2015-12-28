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
// #	define LOGTYPE_DEFAULT    2
// #	define LOGTYPE_USER       4 

#	define SIZE_LOGGER   (sizeof (ez_logger))

#	define FILE_EXISTS(___FNAME)			(access ((___FNAME), F_OK) == 0)
#	define FILE_READABLE(___FNAME)  	(access ((___FNAME), R_OK) == 0)
#	define FILE_WRITABLE(___FNAME)  	(access ((___FNAME), W_OK) == 0)
#	define FILE_EXECUTABLE(___FNAME)  (access ((___FNAME), X_OK) == 0)
#	define FILE_RDWT(___FNAME)   (access ((___FNAME), R_OK | W_OK) == 0)
#	define FILE_RDWTX(___FNAME)     \
	(access ((___FNAME), R_OK | W_OK | X_OK) == 0)

#	define LOGFMTBUFF_LEN 256

// RFC5424 log message levels.
#	define LOGLEVEL_EMERGENCY  1
#	define LOGLEVEL_ALERT      2 
#	define LOGLEVEL_CRITICAL   3
#	define LOGLEVEL_ERROR      4
#	define LOGLEVEL_WARN       5
#	define LOGLEVEL_NOTE       6
#	define LOGLEVEL_INFO       7
#	define LOGLEVEL_DEBUG      8
#	define LOGLEVEL_TRACE      LOGLEVEL_DEBUG
#	define LOGLEVEL_DEFAULT    LOGLEVEL_DEBUG

// logger type
#	define LOGTYPE_CONSOLE  0
#	define LOGTYPE_FILE     1 

typedef struct _ez_logger ez_logger, *pez_logger;
typedef int (*logger_init) (pez_logger, void* args);
typedef int (*logger_release) (pez_logger*);

struct _ez_logger {
	int _type;
	FILE* _fstream;
	logger_init _init;
	logger_release _despose;
};

// create a new logger
extern pez_logger ez_logger_new (logger_init, logger_release, int, void*);

// dispose the logger
extern int ez_logger_despose (pez_logger*);

extern bool ez_logger_alert     (pez_logger, const char*, ...);
extern bool ez_logger_info      (pez_logger, const char*, ...);
extern bool ez_logger_debug     (pez_logger, const char*, ...);
extern bool ez_logger_error     (pez_logger, const char*, ...);
extern bool ez_logger_warn      (pez_logger, const char*, ...);
extern bool ez_logger_notice    (pez_logger, const char*, ...);
extern bool ez_logger_critical  (pez_logger, const char*, ...);
extern bool ez_logger_emergency (pez_logger, const char*, ...);
extern bool ez_logger_trace     (pez_logger, const char*, ...);


#if 0
// log with string
extern bool ez_logger_log (pez_logger, const char*);

// this function will add timestamp automatically
extern bool ez_logger_logln (pez_logger, const char*);

// log with format string
extern bool ez_logger_logf (pez_logger, const char*, ...);
#endif

#ifdef __cplusplus
}
#endif

#endif // ~ _EZ_LOG_H_

