#include "ez.h"
#include "ez_event.h"
// #include "ez_select.h"
#include <stdlib.h>
#include "ez_select.c"

pezevent_loop ezevent_create_eventloop (int _size) {
	pezevent_loop eventloop;
	eventloop = (pezevent_loop) malloc (SIZE_EZEVENT_LOOP);

	if (! eventloop) goto dispose;
	eventloop -> _events = (pezevent_file) 
		malloc (SIZE_EZEVENT_FILE * _size);
	eventloop -> _occured = (pezevent_occured)
		malloc (SIZE_EZEVENT_OCCURED * _size);

	if (! eventloop -> _events || ! eventloop -> _occured) 
		goto dispose;

	eventloop -> _size = _size;
	eventloop -> _canrun = 1;
	eventloop -> _maxfd = -1;

	// initialize depths .
	if (ezselect_init (eventloop) != RTNVAL_SUCC)
		goto dispose;

	return eventloop;
dispose:
	if (eventloop) {
		free (eventloop -> _events);
		free (eventloop -> _occured);
		eventloop -> _events = NULL;
		eventloop -> _occured = NULL;
	}
	return NULL;
}


void ezevent_despose_eventloop (pezevent_loop _loop) {
	if (! _loop) return;
	_loop -> _canrun = 0;
	free (_loop -> _events);
	free (_loop -> _occured);
	_loop -> _events = NULL;
	_loop -> _occured = NULL;
}

void ezevent_stop_eventloop (pezevent_loop _loop) {
	_loop -> _canrun = 0;
}

int ezevent_add_fileevent (pezevent_loop _loop, int _fd, 
		int _mask, ezevent_fileproc _proc, void* _datas) {
	if (! _loop) return RTNVAL_ERR;
	if (_fd >= _loop -> _size) return RTNVAL_ERR;
	// we'd better return something.
	ezselect_addevent (_loop, _fd, _mask);

	pezevent_file ptr = &_loop -> _events [_fd];
	ptr -> _event_mask |= _mask; // we cannot sure which _event_mask holding another event masks;
	if (_mask & EE_READABLE) ptr -> _readf = _proc;
	if (_mask & EE_WRITABLE) ptr -> _writef = _proc;
	ptr -> _datas = _datas;

	// update max fd
	if (_fd > _loop -> _maxfd)
		_loop -> _maxfd = _fd;
	return RTNVAL_SUCC;
}

void ezevent_rm_fileevent (pezevent_loop _loop, int _fd, int _mask) {
	if (! _loop || _loop -> _size <= _fd) return;
	pezevent_file ptr = &_loop -> _events [_fd];
	
	if (_mask & EE_NONE) return;
	ptr -> _event_mask &= ~_mask;

	if (_fd == _loop -> _size && ptr -> _event_mask & EE_NONE) {
		int idx = _loop -> _size - 1;
		ezselect_rmevent (_loop, _fd, _mask); // remove from depth register.
		// update maxfd
		for (; idx >= 0; -- idx)
			if (_loop -> _events [idx]._event_mask != EE_NONE) break;
		_loop -> _maxfd = idx;
	}
}

// one event cricle.
int ezevent_process_loop (pezevent_loop _loop, int _proc_flag) {
	int processed = 0, eventscount = 0, idx = 0;
	struct timeval tv;
	if (! _loop || _proc_flag == EE_NONE_EVENT) return processed;
	// default, it's a good idea to make it configured.
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	// depths API get $eventscount;
	eventscount = ezselect_poll (_loop, &tv);

	for (; idx < eventscount; ++ idx) {
		int mask, fd;
		fd = _loop -> _occured [idx]._fd;
		pezevent_file ptr = &_loop -> _events [fd];
		mask = _loop -> _occured [idx]._event_mask;

		// read process
		if (mask & ptr -> _event_mask & EE_READABLE) {
			ptr -> _readf (_loop, fd, mask, ptr -> _datas);
		}
		if (mask & ptr -> _event_mask & EE_WRITABLE) {
			ptr -> _writef (_loop, fd, mask, ptr -> _datas);
		}
		++ processed;
	}
	return processed;
}

void ezevent_start_loop (pezevent_loop _loop) {
	_loop -> _canrun = 1;
	while (_loop -> _canrun) {
		ezevent_process_loop (_loop, EE_ALL_EVENT);
	}
}

int ezevent_get_size (pezevent_loop _loop) {
	return _loop -> _size;
}

int ezevent_reset_size (pezevent_loop _loop, int _newsize) {
	int i = _newsize - 1;
	if (_newsize <= 0 || _newsize <= _loop -> _size) 
		return RTNVAL_SUCC;

	// resize depth.
	if (ezselect_resize (_loop, _newsize) != RTNVAL_SUCC)
		return RTNVAL_FAIL;

	_loop -> _events = realloc (_loop -> _events, 
			SIZE_EZEVENT_FILE* _newsize);
	_loop -> _occured = realloc (_loop -> _events,
			SIZE_EZEVENT_OCCURED * _newsize);

	for (; i >= _loop -> _size; -- i)
		_loop -> _events [i]._event_mask = EE_NONE;

  _loop -> _size = _newsize;
	return RTNVAL_SUCC;
}

