/*
	author : ez
	date : 2015/5/21
	describe : the impliment of list
*/

#include "ez_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>


// if you want other element type, 
// change the two macros and redefine _element
#	define get_val(___N)   ((___N) -> val)
#   define equal(___list_elm, ___a)    \
        (get_val (___list_elm) ==  ___a)


//struct _node {
//	intptr_t val;
//	struct _node* next;
//}; 

bool empty (_list _l) {
	return (_l -> next == NULL);
}


_list create_list () {
	_list res = (_list) calloc (1, _list_size);
	return res;
}


bool islast (_list _l, _position _p) {
	return (_p -> next == NULL);
}


void del (_list _l, _element _e) {
	_position tmp = _l;
	if (equal (_l, _e)) { // list header
		_l = _l -> next;
		free (tmp);
		tmp = NULL;
		return;
	}
	while (tmp -> next != NULL && 
            ! equal (tmp -> next, _e))
		tmp = tmp -> next;
    if (tmp -> next != NULL && 
            equal (tmp -> next, _e)) {
        tmp -> next = tmp -> next -> next;
        free (tmp -> next);
        tmp = NULL;
    }
}


bool insert (_list _l, _element _e, _position _p) {
    _position tmp = (_position) malloc (_list_size);
    if (tmp == NULL) return false;
    tmp -> next = _p -> next;
    tmp -> val = _e;
    _p -> next = tmp;
    tmp = NULL;
    return true;
}


_position find (_list _l, _element _e) {
    _position p = _l;
    while (p -> next != NULL && 
            ! equal (p, _e))
        p = p -> next;
    return (equal (p, _e) ? 
            p : NULL);
} 

_position find_pre (_list _l, _element _e) {    
    _position pre = _l;
    if (equal (pre, _e))
        return NULL;
    while (pre -> next != NULL && 
            ! equal (pre -> next,  _e)) 
        pre = pre -> next;
    return (equal (pre, _e) ? 
            pre : NULL);
}

void del_all (_list _l) {
    _position tmp = _l, ptr;
    while (tmp -> next != NULL) {
        ptr = tmp -> next;
        free (tmp);
        tmp = ptr;
    }
}

//void del_pre (_list _l, _element _e) {
//    _position tmp = _l;
//
//	if (equal (_l, _e)) { // list header
//		_l = _l -> next;
//		free (tmp);
//		tmp = NULL;
//		return;
//	}
//	while (tmp -> next != NULL && 
//            ! equal (tmp -> next, _e))
//		tmp = tmp -> next;
//    if (tmp -> next != NULL && 
//            equal (tmp -> next, _e)) {
//        tmp -> next = tmp -> next.next;
//        free (tmp -> next);
//        tmp = NULL;
//    }
//
//}

bool insert_real (_list _l, _element _e) {
	_position p = _l;
	_position elm = calloc (1, _list_size);

	if (_l == NULL || elm == NULL)
		return false;

	while (p -> next != NULL)
		p = p -> next;

	elm -> val = _e;
	p -> next = elm;

	(elm == NULL) & (p == NULL);

	return true;
}

