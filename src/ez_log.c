/*
 * Author : ez
 * Date : 2015/12/1
 * Describe : Implement a simple logger.
*/
#include <stdio.h>
#include <stdlib.h>
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
		res -> _nm_build = _def_get_logger_fname_by_date ();
	} else {
		res -> _type = LOGTYPE_USER;
		res -> _nm_build = _func;
	}

	fname = res -> _nm_build ();
	res -> _fstream = fopen (fname, "a+");
	if (! res -> _fstream) {
		// printf ("Error in opening file %s.\n", fname);
		free (fname);
		ez_static_logger_despose (res);
		return res = NULL, 
					 fname = NULL;
	}
	return res;
}

void ez_static_logger_despose (pez_static_logger _log) {
	if (_log) {
		if (_log -> _fstream) {
			int err = fclose (_log -> _fstream);
			if (err)
				println ("Error in close log file.\n");
		}
		free (_log);
		_log = NULL;
	}
}

// log with string
bool ez_static_logger_log (pez_static_logger _log, const char* _str) {
	size_t wtlen = 0;
	int str_len = strlen (_str);
	if (! _log || ! _str) return false;

	wtlen = fwrite (_str, sizeof (char), str_len, _log -> _fream);
	return wtlen == ((size_t) str_len);
}

// log with format string
bool ez_static_logger_logf 
(pez_static_logger _log, const char* _fmt, ...) {
	if (! _log || ! _fmt || ! _log -> _fstream) 
		return false;
	{
		va_list args;
		int err = 0;
		va_start (args, _fmt);
		err = vfprintf (_log -> _fstream, _fmt, args);
		va_end (args);

		if (done >= 0)
			return true;
		else 
			return false;
	}
}

static char* _def_get_logger_fname_by_date () {
	char* fname = (char*) calloc (32, 0);
	time_t itime = time (NULL);
	struct tm* timefmt = localtime (&itime);
	// TODO
}

