/*
 * Author : ez
 * Date : 2015/12/1
 * Describe : Implement a simple logger.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "ez_log.h"

static char* _def_get_logger_fname_by_date ();

pez_logger 
ez_logger_new (fname_build _func) {
	char* fname = NULL;
	pez_logger res = 
		(pez_logger) malloc (SIZE_LOGGER);
	int err;

	if (! res) return NULL;

	if (! _func) {
		res -> _type = LOGTYPE_DEFAULT;
		res -> _nm_build = _def_get_logger_fname_by_date;
	} else {
		res -> _type = LOGTYPE_USER;
		res -> _nm_build = _func;
	}

	fname = res -> _nm_build ();
	res -> _fstream = fopen (fname, "a+");
	if (! res -> _fstream) {
		// printf ("Error in opening file %s.\n", fname);
		free (fname);
		ez_logger_despose (&res);
                fname = NULL;
	}
	return res;
}

void ez_logger_despose (pez_logger* _log) {
	if (*_log) {
		if ((*_log) -> _fstream) {
			int err = fclose ((*_log) -> _fstream);
			if (err)
				println ("Error in close log file.\n");
		}
		free (*_log);
		*_log = NULL;
	}
}

// log with string
bool ez_logger_log (pez_logger _log, const char* _str) {
	size_t wtlen = 0;
	int str_len = strlen (_str);
	if (! _log || ! _str) return false;

	wtlen = fwrite (_str, sizeof (char), str_len, _log -> _fstream);
	return wtlen == ((size_t) str_len);
}

// log with format string
bool ez_logger_logf 
(pez_logger _log, const char* _fmt, ...) {
	if (! _log || ! _fmt || ! _log -> _fstream) 
		return false;
	{
		va_list args;
		int err = 0;
		va_start (args, _fmt);
		err = vfprintf (_log -> _fstream, _fmt, args);
		va_end (args);

		if (err >= 0)
			return true;
		else 
			return false;
	}
}

// this function will add timestamp automatically
inline bool
ez_logger_logln (pez_logger _log, const char* _str) {

  return false;
}

static char* _def_get_logger_fname_by_date () {
	char* fname = (char*) calloc (0x10, 0);
	time_t itime = time (NULL);

        // this is static memory.
        size_t len = strftime (fname, 0x10, 
            "Log%Y%m%d.log", localtime (&itime));
        if (len >= 0)
          return fname;
        else {
          free (fname);
          return fname = NULL;
        }
}


