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

#	define __safe_clean(cls, p)   \
	do {     \
		if (cls && p) cls (p); \
	} while (0)


static bool __safe_equal (cmp_func cmp, pez_listnode _p, T _e) {
	return cmp ? (cmp (_p -> val, _e) == EQUAL) : 
		(_p -> val == _e);
}

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

/* TODO...
 * Get the head element of list.
 * $1: List entry ptr.
 * Return element. If the list is empty, return NULL.
 */
pez_listnode ez_list_getbyidx (pez_list);

/*
   Insert an element at the top of list.
   Return true if successful, else return
   false.
   NOTE: if the *@1 is NULL, a new list will
   be created and value will set to @2
*/
pez_listnode ez_list_pushtail (pez_list _l, const T _e) {
	pez_listnode node;
	if (! _l) return NULL;

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
pez_listnode ez_list_pushhead (pez_list _l, const T _e) {
	pez_listnode node;
	if (! _l) return NULL;

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
	if (! _l || _idx < 0) return NULL;

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
	pez_listnode pre;
	if (! _l || ez_list_isempty (_l)) return;

	pre = _l -> elms;
	if (__safe_equal (_l -> cmp, pre -> val, _e))
		ez_list_pophead (_l);

	while (pre) {
		pez_listnode p = pre -> next;
		if (! p) break;

		if (__safe_equal (_l -> cmp, p -> val, _e)) {
			__safe_clean (_l -> cls, p -> val);
			pre -> next = p -> next;
			_l -> size --;
			free (p); p = NULL;
			return;
		} else
			pre = p;
	}
}

/* TODO...
 * Delete all the elements whose value equals to $1.
 * This function will iterate the whole list and delete
 * each found note.
 * $1: List entry ptr.
 * $2: value ptr (void*).
 * Note if function cmp_func doesn't be assigned, we just
 * compare ptr value.
 * Return the number of deleted element.
 */
extern int ez_list_delall (pez_list, const T);

/* TODO...
 * Find the first element equalling argument $2,
 * If such an element doesn't exist, return NULL,
 * else return the node.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
pez_listnode ez_list_search (pez_list, const T) {
  while (p -> next && ! equal (p, _e)) p = p -> next;
	return p;
} 

/* TODO...
 * Find the pre element of the equalling argument $2, 
 * If such element doesn't exist or the front of list 
 * element doesn't exist, return NULL, else return the
 * node.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
pez_listnode ez_list_search_pre (pez_list _l, const T _e) {    

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

/* TODO...
 * Find the post element of the equalling argument $2, 
 * If such element doesn't exist or the post of 
 * element doesn't exist, return NULL, else return the
 * node.
 * $1: List entry ptr.
 * $2: Element with type void*.* 
 */
pez_listnode ez_list_search_post (pez_list, const T);

/*
 * Pop head element if existing. No effect if it's empty.
 * $1: List entry ptr.
 */
void ez_list_pophead (pez_list _l) {
	pez_listnode p;
	if (ez_list_isempty (_l)) return;
	p = _l -> elms;
	_l -> elms = p -> next;
	__safe_clean (_l, p -> val);
	_l -> size --;
	free (p); p = NULL;
}


/*
 * Pop tail element if existing. No effect if list's empty.
 * $1: List entry ptr.
 */
void ez_list_poptail (pez_list _l) {
	pez_listnode pre;
	if (ez_list_isempty (_l)) return;
	pre = _l -> elms;

	/* Only one element. */
	if (! pre -> next) {
		__safe_clean (_l -> cls, pre -> val);
		_l -> size --;
		_l -> tail = NULL;
		free (pre); _l -> elms = NULL;
		return;
	}

	while (pre) {
		pez_listnode p = pre -> next;
		if (p && ! p -> next) {
			__safe_clean (_l -> cls, p -> val);
			_l -> size --;
			free (p); _l -> tail = pre;
			return;
		} else
			pre = p;
	}
}


/*
 * Delete all the elements in the list.
 * $1: List entry ptr.
 * Return the number of deleted element.
 */
int ez_list_clean (pez_list _l) {
  pez_listnode ptr = _l -> elms;
	int count = 0;

	while (ptr) {
		pez_listnode tmp = ptr -> next;
		__safe_clean (_l -> cls, ptr -> val);
		free (ptr); _l -> size --; 
		count ++;
		_l -> elms = ptr = tmp;
	}
	return count;
}

/*
 * Release all the memory in list. If its cls_func is set,
 * invoke it for each element.
 * $1: List ptr. If NULL, doing nothing.
 */
void ez_list_dispose (pez_list* _l) {
	if (! *_l) return;
	ez_list_clean (*_l);
	free (*_l); *_l = NULL;
}


/* TODO...
 * Duplicate a new list entry from $1.
 * $1: List entry to be copied.
 * Return the list entry if successful. else return NULL.
 */
extern pez_list ez_list_duplicate (pez_list);


// TODO...
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


