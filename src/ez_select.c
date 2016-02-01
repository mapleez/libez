#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "ez_event.h"

typedef struct ezselect_status {
	/* the sources. */
	fd_set _reads, _writes;

	/* as backup. */
	fd_set _backrd, _backwr;
} ezselect_status, 
		*pezselect_status;

#	define SIZE_SELECT_STATUS  (sizeof (struct ezselect_status))

static int ezselect_init (pezevent_loop _loop) {
	if (! _loop) return RTNVAL_ERR;
	pezselect_status state = 
		(pezselect_status) malloc (SIZE_SELECT_STATUS);
	if (! state) return RTNVAL_FAIL;
	FD_ZERO (&state -> _reads);
	FD_ZERO (&state -> _writes);

	FD_ZERO (&state -> _backrd);
	FD_ZERO (&state -> _backwr);
	_loop -> _dep_data = (void*) state;
	return RTNVAL_SUCC;
}

static int ezselect_resize (pezevent_loop _loop, int _newsize) {
	if (_newsize >= FD_SETSIZE) return RTNVAL_FAIL;
	return RTNVAL_SUCC;
}

static void ezselect_dispose (pezevent_loop _loop) {
	free ((pezselect_status) _loop -> _dep_data);
	_loop -> _dep_data = NULL;
}

static void ezselect_rmevent
(pezevent_loop _loop, int _fd, int _mask) {
	if (! _loop || ! _loop -> _dep_data) return;
	pezselect_status status = _loop -> _dep_data;

	if (_mask & EE_READABLE) FD_CLR (_fd, &status -> _backrd);
	if (_mask & EE_WRITABLE) FD_CLR (_fd, &status -> _backwr);
}

static void ezselect_addevent
(pezevent_loop _loop, int _fd, int _mask) {
	pezselect_status status;
	if (! _loop || ! _loop -> _dep_data) return;
	status = _loop -> _dep_data;

	if (_mask & EE_READABLE) FD_SET (_fd, &status -> _backrd);
	if (_mask & EE_WRITABLE) FD_SET (_fd, &status -> _backwr);
}

static int ezselect_poll (pezevent_loop _loop, struct timeval* _tv) {
	pezselect_status status;
	int fd, countevent = 0;
	if (! _loop || ! _loop -> _dep_data) return 0;
	status = _loop -> _dep_data;

	memcpy (&status -> _reads, &status -> _backrd, sizeof (fd_set));
	memcpy (&status -> _writes, &status -> _backwr, sizeof (fd_set));
	if (select (_loop -> _maxfd + 1, &status -> _reads, 
				&status -> _writes, NULL, _tv)) {
		for (fd = 0; fd <= _loop -> _maxfd; ++ fd) {
			int mask = 0;
			ezevent_file* fe = &_loop -> _events [fd];
			if (fe -> _event_mask == EE_NONE) continue;
			if (fe -> _event_mask & EE_READABLE && 
					FD_ISSET (fd, &status -> _reads))
				mask |= EE_READABLE;
			if (fe -> _event_mask & EE_WRITABLE &&
					FD_ISSET (fd, &status -> _writes))
				mask |= EE_WRITABLE;
			_loop -> _occured [countevent]._fd = fd;
			_loop -> _occured [countevent]._event_mask = mask;
			++ countevent;
		}
	}
	return countevent;
}


