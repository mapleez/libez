#ifndef _EZ_EVENT_H_
#	define _EZ_EVENT_H_

// event mask;
#	define EE_NONE 0
#	define EE_READABLE 1
#	define EE_WRITABLE 2

// process flag;
#	define EE_FILE_EVENT 1
#	define EE_NONE_EVENT 0 
#	define EE_ALL_EVENT (EE_FILE_EVENT)

#	define RTNVAL_SUCC 1
#	define RTNVAL_FAIL 0 
#	define RTNVAL_ERR  -1

struct ezevent_loop;

// $0 = event loop ptr
// $1 = file descriptor
// $2 = event mask
// $3 = data ptr
typedef void (*ezevent_fileproc)
(struct ezevent_loop*, int, int, void*);

// use index as his fd;
typedef struct ezevent_file {
	int _event_mask;
	ezevent_fileproc _readf;
	ezevent_fileproc _writef;
	void* _datas;
} ezevent_file,
		*pezevent_file;

typedef struct ezevent_occured {
	int _event_mask;
	int _fd;
} ezevent_occured,
		*pezevent_occured;

typedef struct ezevent_loop {
	int _maxfd;
	int _size;
	pezevent_file _events;
	pezevent_occured _occured; // we fill it in order.
	int _canrun;
	void* _dep_data;
} ezevent_loop,
	*pezevent_loop;

// size
#	define SIZE_EZEVENT_LOOP (sizeof (ezevent_loop))
#	define SIZE_EZEVENT_FILE (sizeof (ezevent_file))
#	define SIZE_EZEVENT_OCCURED (sizeof (ezevent_occured))

pezevent_loop ezevent_create_eventloop (int _size);
void ezevent_despose_eventloop (pezevent_loop);
void ezevent_stop_eventloop (pezevent_loop);

int ezevent_add_fileevent (pezevent_loop, int _fd, 
		int _mask, ezevent_fileproc _proc, void* _datas);
void ezevent_rm_fileevent (pezevent_loop, int _fd, int _mask);

int ezevent_process_loop (pezevent_loop, int _proc_flag);
void ezevent_start_loop (pezevent_loop);
int ezevent_stop_loop (pezevent_loop);

int ezevent_get_size (pezevent_loop);
int ezevent_reset_size (pezevent_loop, int);

#endif // ~ _EZ_EVENT_H_

