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
static char* _def_get_logger_console_by_date ();

// static char _buff [0x40];
static fname_build _default_builder [] = {
	_def_get_logger_console_by_date,
	_def_get_logger_fname_by_date
};


pez_logger 
ez_logger_new (fname_build _func, int _type) {
	char* fname = NULL;
	pez_logger res = 
		(pez_logger) malloc (SIZE_LOGGER);
	int err;

	if (! res) return NULL;

	res -> _type = _type;
	if (! _func) {
		// res -> _type = LOGTYPE_DEFAULT; 
		// _def_get_logger_fname_by_date;
		res -> _nm_build = _default_builder [_type];
	} else {
		// res -> _type = LOGTYPE_USER;
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
bool ez_logger_logln 
(pez_logger _log, const char* _str) {
  char buff [0x30] = {0, };
  time_t timestamp = time (NULL);
  bool flag = !! strftime (buff, 0x30, 
      "[%s] %Y/%m/%d %H:%M:%S", localtime (&timestamp));
  return 
    flag && ez_logger_logf (_log, "%s %s\n", buff, _str);
}

// default function to get logger file name.
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

static char* _def_get_logger_console_by_date () {
	return "STDIO";
}


bool ez_logger_alert     (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[A] ", localtime (&timestamp));
	if (! time_len)
		return false;

	va_start (args, _fmt);
	stored_len = vsprintf (buff + time_len, _fmt, args);
	va_end (args);
	if (! stored_len)
		return false;
	stored_len += time_len;
	buff [stored_len ++] = '\n';
  return stored_len == fwrite (buff, sizeof (char), 
			stored_len, _log -> _fstream);
}

bool ez_logger_info      (pez_logger _log, const char* _fmt, ...) {}
bool ez_logger_debug     (pez_logger _log, const char* _fmt, ...) {}
bool ez_logger_error     (pez_logger _log, const char* _fmt, ...) {} 
bool ez_logger_warn      (pez_logger _log, const char* _fmt, ...) {}
bool ez_logger_notice    (pez_logger _log, const char* _fmt, ...) {}
bool ez_logger_critical  (pez_logger _log, const char* _fmt, ...) {}
bool ez_logger_emergency (pez_logger _log, const char* _fmt, ...) {}
bool ez_logger_trace     (pez_logger _log, const char* _fmt, ...) {}

