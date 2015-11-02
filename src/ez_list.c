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

bool ez_list_empty (_list _l) {
	return (_l -> next == NULL);
}


_list ez_list_create () {
	_list res = (_list) calloc (1, _list_size);
	return res;
}


bool ez_list_islast (_list _l, _position _p) {
	return (_p -> next == NULL);
}


/*
   Delete the element from list,
   if the element doesn't exist, nothing
   will be done.
*/
void 
ez_list_del (_list _l, _element _e) {

	_position tmp = _l;
	if (equal (_l, _e)) { // list header
		_l = _l -> next;
		free (tmp);
		tmp = NULL;
		return;
	}

	while (tmp -> next) {
		if (! equal (tmp -> next, _e))
			tmp = tmp -> next;
		else {
			tmp -> next = tmp -> next -> next;
			free (tmp -> next);
			tmp -> next = NULL;
		}
	}
}


bool ez_list_insert (_list _l, _element _e, _position _p) {
    _position tmp = (_position) malloc (_list_size);
    if (tmp == NULL) return false;
    tmp -> next = _p -> next;
    tmp -> val = _e;
    _p -> next = tmp;
    tmp = NULL;
    return true;
}


/*
   Find the first element equaling argument @2,
   If such element doesn't exist, return NULL,
   else return position.
*/
_position 
ez_list_find (_list _l, _element _e) {

    _position p = _l;
    while (p -> next && ! equal (p, _e))
        p = p -> next;
	return p;
    // return (equal (p, _e) ? 
    //         p : NULL);
} 

_position 
ez_list_find_pre (_list _l, _element _e) {    

    _position pre = _l;
    if (equal (pre, _e))
        return NULL;
    while (pre -> next && 
            ! equal (pre -> next,  _e)) 
        pre = pre -> next;
	return pre;
    // return (equal (pre, _e) ? 
    //         pre : NULL);
}

void ez_list_del_all (_list _l) {
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

bool ez_list_insert_real (_list _l, _element _e) {
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

