/*
	author : ez
	date : 2015/5/21
	describe : the impliment of list
*/

#include "ez_list.h"
#include "ez.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static bool __safe_equal (cmp_func, pez_listnode, T);




static bool __safe_equal (cmp_func cmp, pez_listnode _p, T _e) {
	return cmp ? (cmp (_p -> val, _e) == EQUAL) : 
		(_p -> val == _e)
}

// #	define get_val(___N)   ((___N) -> val)
// #   define equal(___list_elm, ___a)    \
//         (get_val (___list_elm) ==  ___a)

/*
 * Return the number of element 
 * in the list;
 * NOTE: A new list made by ez_list_create ()
 * will include one element originally.
 */
// int
// ez_list_count (const _list _l) {
// 	_position ptr = _l;
// 	int i = 1;
// 	while (ptr -> next) {
// 		++ i;
// 		ptr = ptr -> next;
// 	}
// 	return i;
// }

/*
 * Create a List,
 * Return the pointer to the first
 * element if successful,  else 
 * return NULL.
 */
pez_list ez_list_create () {
	pez_list list = (pez_list) malloc (EZ_LIST_SIZE);
	if (! list) return NULL;
	list -> elms = list -> tail = NULL;
	list -> size = 0;

	/* We donot set default func. */
	list -> cmp = NULL;
	list -> cls = NULL;
	list -> dup = NULL;
	return list;
}


/*
 * Check whether the element whose value equals $2 is
 * the last element in a list.
 * Return true or false.
 */
bool ez_list_islast (const pez_list _l, const T _p) {
	if (! _l || ! _p || ez_list_isempty (_l)) return false;
	pez_listnode tail = _l -> tail;
	return __safe_equal (_l -> cmp, tail, _p);
}

pez_listnode ez_list_gethead (pez_list _l) {
	if (! _l || ez_list_isempty (_l)) return NULL;
	return _l -> elms;
}

pez_listnode ez_list_gettail (pez_list _l) {
	if (! _l || ez_list_isempty (_l)) return NULL;
	return _l -> tail;
}

/*
   Insert an element at the top of list.
   Return true if successful, else return
   false.
   NOTE: if the *@1 is NULL, a new list will
   be created and value will set to @2
*/
pez_listnode ez_list_pushtail (pez_list _l, const T _e) {
	pez_listnode node;
	if (! *_l) return NULL;

	node = (pez_listnode) 
		calloc (1, EZ_LISTNODE_SIZE);
	if (! node) return NULL;
	node -> val = _e;
	node -> next = NULL;
	_l -> tail -> next = node;
	_l -> size ++;
	return node;
}

/*
 * Insert an element at the end of list. 
 * $1: List ptr.
 * $2: Element value.
 * Return the node ptr if successful, otherwise return NULL.
 */
pez_listnode ez_list_pushtail (pez_list _l, const T _e) {
	pez_listnode node;
	if (! *_l) return NULL;

	node = (pez_listnode)
		calloc (1, EZ_LISTNODE_SIZE);
	if (! node) return NULL;
	node -> val = _e;
	node -> next = _l -> elms;
	_l -> elms = node;
	_l -> size ++;
	return node;
}


/*
 * Insert an element into list by index.
 * $1 list ptr
 * $2 an element to be inserted.
 * $3 the index at which will be inserted.
 * Return the node ptr if successful, else return NULL.
 */
pez_listnode ez_list_pushbyidx (pez_list _l, 
	const T _e, int _idx) {
	pez_listnode node;
	pez_listnode ptr;
	if (! *_l || _idx < 0) return NULL;

	/* Push at the head. */
	if (_idx == 0) 
		return ez_list_pushhead (_l, _e);

	/* Push at the tail. */
	if (_idx - 1 >= _l -> size) 
		return ez_list_pushtail (_l, _e);

	node = (pez_listnode) calloc (1, EZ_LISTNODE_SIZE);
	if (! node) return NULL;
	node -> val = _e;

  /* TODO Test whether ptr could be NULL. */
	ptr = _l -> elms;
	while (ptr) {
		if (_idx != 1) {
			ptr = ptr -> next;
			_idx --;
		} else {
			node -> next = ptr -> next;
			ptr -> next = node;
			_l -> size ++;
		}
	}
	return node;
}

/*
 * Delete the element from the list,
 * if the element doesn't exist, nothing
 * will be done.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
void ez_list_del (pez_list _l, const T _e) {
	pez_list pre;
	if (! _l) return;

	pre = _l -> elms;
	if (__safe_equal (pre -> val, _e))
		ez_list_pophead (_l);

	pre = pre -> next;
	/* TODO... */
	while (pre) {
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


_list ez_list_reverse (_list _head) {
	_list head, pre, next;
	head = _head;

	/* Only one elm */
	pre = head;
	next = head -> next;
	if (! next) return head;

	while (next) {
		pre -> next = next -> next;
		next -> next = head;
		/* set 2 pointers to 
			 right position */
		head = next;
		next = pre -> next;
	}
	_head -> next = NULL;
	return head;
}


