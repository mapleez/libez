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

/*
   Check whether the list is empty.
   return true if it is, otherwise 
   false;

   WARNING: because of the header of list,
   each created list will include at least
   one element, so in this version, the 
   function always return true.
*/
bool ez_list_empty (const _list _l) {
	return (_l -> next == NULL);
}

/*
   Return the number of element 
   in the list;

   NOTE: A new list made by ez_list_create ()
   will include one element originally.
*/
int
ez_list_count (const _list _l) {
	_position ptr = _l;
	int i = 1;
	while (ptr -> next) {
		++ i;
		ptr = ptr -> next;
	}
	return i;
}

/*
   Create a List,

   return the pointer to the first
   element if successful,  else 
   return NULL.
*/
_list ez_list_create () {
	_list res = (_list) calloc (1, _list_size);
	return res;
}


/*
   Check whether the position is
   the last element in a list.

   return true or false.
*/
bool ez_list_islast 
	(const _list _l, const _position _p) 
{
	return (_p -> next == NULL);
}


/*
   Insert an element at the top of list.
   Return true if successful, else return
   false.
   
   NOTE: if the *@1 is NULL, a new list will
   be created and value will set to @2
*/
bool ez_list_insert_top 
	(_list* _l, const _element _e) 
{
	_position ptr = 
		(_position) calloc (1, _node_size);
	if (! *_l && ! ptr) return false;
	get_val (ptr) = _e;
	ptr -> next = *_l;
	*_l = ptr;
	return true;
}

/*
   Delete the element from list,
   if the element doesn't exist, nothing
   will be done.
*/
void 
ez_list_del (_list _l, const _element _e) {

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


/*
   Insert an element into list.
   @1 list ptr
   @2 an element to be inserted.
   @3 the position that will be inserted ahead.

   return true if successful, else return false;
*/
bool ez_list_insert 
	(_list _l, const _element _e, _position _p) 
{
    _position tmp = 
		(_position) malloc (_list_size);
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
ez_list_find (_list _l, const _element _e) {

    _position p = _l;
    while (p -> next && ! equal (p, _e))
        p = p -> next;
	return p;
    // return (equal (p, _e) ? 
    //         p : NULL);
} 

/*
   Find the pre element of the equaling 
   argument @2, If such element doesn't 
   exist or the front of list element 
   equals @2, return NULL, else return 
   its position.
*/
_position 
ez_list_find_pre (_list _l, const _element _e) {    

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

/*
   Delete all elements in the list.
   The @1 will be set to NULL;
*/
void ez_list_del_all (_list _l) {
    _position tmp = _l, ptr;
	do {
		ptr = tmp -> next;
		free (tmp);
		tmp = ptr;
	} while (ptr);
	_l = NULL;
    // while (tmp -> next != NULL) {
    //     ptr = tmp -> next;
    //     free (tmp);
    //     tmp = ptr;
    // }
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

/*
   Insert an element at the end of list.
   Return true if successful, otherwise
   return false.
*/
bool 
ez_list_insert_real (_list _l, const _element _e) {
	_position p = _l;
	_position elm = calloc (1, _list_size);

	if (!_l || !elm)
		return false;

	while (p -> next != NULL)
		p = p -> next;

	elm -> val = _e;
	p -> next = elm;

	(elm = NULL) && (p = NULL);
	return true;
}


