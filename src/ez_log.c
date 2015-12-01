/*
 * Author : ez
 * Date : 2015/12/1
 * Describe : Implement a simple logger.
*/
#include <stdio.h>
#include <stdlib.h>
#include "ez_log.h"

static char* _def_get_logger_fname_by_date ();

pez_logger 
ez_logger_new (fname_build _func) {
	char* fname = NULL;
	pez_logger res = 
		(pez_logger) malloc (SIZE_LOGGER);

	if (! res) return NULL;

	if (! _func) {
		res -> _type = LOGTYPE_DEFAULT;
		res -> _nm_build = _def_get_logger_fname_by_date ();
	} else {
		res -> _type = LOGTYPE_USER;
		res -> _nm_build = _func;
	}

	fname = res -> _nm_build ();
	// TODO

	return res;
}

void ez_static_logger_despose (pez_static_logger _log) {
	return;
}

// log with string
bool ez_static_logger_log (pez_static_logger _log, const char* _str) {
	return false;
}

// log with format string
bool ez_static_logger_logf 
(pez_static_logger _log, const char* _fmt, const char* _str, ...) {
	return false;
}

