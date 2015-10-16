#include <ez_queue.h>
#include <stdio.h>
#include <stdlib.h>



bool full_queue (_queue _q) {
	
	return false;
}


bool empty_queue (_queue) {

	return false;
}


_queue create_queue (int _maxcapa) {
	_queue q = (_queue) malloc (_queue_size);
	if (! q) {
		q -> array = (_element*) 
			calloc (_maxcapa, _element_size);
		q -> capacity = _maxcapa;
		q -> front = q -> real = 0;
	}
	return q;
}


void dispose_queue (_queue _q) {
	if (! _q) {
		free (_q);
		_q = NULL;
	}
}


bool enqueue (_queue _q, _element _e) {
	if (! _q)
		return false;
	_q -> array [_q -> real ++] = _e;
	return true;
}


bool dequeue (_queue) {
	if (! _q)
		return false;
}


_element* front (_queue) {

	return NULL;
}


_element* frontanddequeue (_queue) {

	return NULL;
}

