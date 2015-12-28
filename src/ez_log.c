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

static int _def_init_filelogger (pez_logger, void*);
static int _def_init_consolelogger (pez_logger, void*);

static int _def_release_consolelogger (pez_logger*);
static int _def_release_filelogger (pez_logger*);

// static char _buff [0x40];
static logger_init _default_init [] = {
	_def_init_consolelogger,
	_def_init_filelogger
};

static logger_release _default_despose [] = {
	_def_release_consolelogger,
	_def_release_filelogger
};

pez_logger ez_logger_new 
(logger_init _init, logger_release _release, int _type, void* _args) {
	int init_res = 0;
	pez_logger res = (pez_logger) malloc (SIZE_LOGGER);
	if (! res) return NULL;
	res -> _type = _type;
	res -> _init = _init ? _init : _default_init [_type];
	res -> _despose = _release ? _release : _default_despose [_type];
	init_res = res -> _init (res, _args);
	if (! init_res) res -> _despose (&res);
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

#if 0
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

#endif

// default function to get logger file name.
static int _def_init_filelogger (pez_logger _log, void* _args) {
  char fname [0x10] = {0, };// = (char*) calloc (0x10, 0);
  time_t itime = time (NULL);
  
  // this is static memory.
  size_t len = strftime (fname, 0x10, 
      "Log%Y%m%d.log", localtime (&itime));
	if (len <= 0)
		return 0;
	_log -> _fstream = fopen (fname, "a+");
	if (! _log -> _fstream) 
		return 0;
	return 1;
}

static int _def_init_consolelogger
(pez_logger _log, void* _args) {
	// stdout file stream
	_log -> _fstream = stdout;
	return 1;
}

static int _def_release_filelogger (pez_logger* _log) {
	if (*_log) {
		if ((*_log) -> _fstream) {
			int err = fclose ((*_log) -> _fstream);
			if (err) {
				println ("Error in close log file.\n");
				return 0;
			}
		}
		free (*_log);
		*_log = NULL;
	}
	return 1;
}

static int _def_release_consolelogger (pez_logger* _log) {
	if (*_log) {
		ez_logger_info (*_log, "Console logger despose...done!");
		free (*_log);
		*_log = NULL;
	}
	return 1;
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

bool ez_logger_info      (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[I] ", localtime (&timestamp));
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

bool ez_logger_debug     (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[D] ", localtime (&timestamp));
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

bool ez_logger_error     (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[E] ", localtime (&timestamp));
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

bool ez_logger_warn      (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[W] ", localtime (&timestamp));
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

bool ez_logger_notice    (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[N] ", localtime (&timestamp));
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

bool ez_logger_critical  (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[C] ", localtime (&timestamp));
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

bool ez_logger_emergency (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[M] ", localtime (&timestamp));
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

bool ez_logger_trace     (pez_logger _log, const char* _fmt, ...) {
  char buff [LOGFMTBUFF_LEN] = {0, };
	va_list args;
	int time_len = 0, stored_len = 0;
  time_t timestamp = time (NULL);
  time_len = strftime (buff, LOGFMTBUFF_LEN, 
      "[%s] %Y/%m/%d %H:%M:%S[T] ", localtime (&timestamp));
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

