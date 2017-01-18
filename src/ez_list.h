/*
 * author : ez
 * date : 2015/5/21
 * describe : The linked list declaration. It's not a thread-safe
 * implementation
 */

#ifndef _EZ_LIST_H_
#	define _EZ_LIST_H_

#include <stdbool.h>
#include "ez.h"

#	define EZ_LIST_SIZE      (sizeof (struct _ez_list))
#	define EZ_LISTNODE_SIZE  (sizeof (struct _ez_listnode))

/*
 * Use as a node of each element in list.
 */
typedef struct _ez_listnode {
	/* Point to next. */
	struct _ez_listnode* next;

	/* Value. */
	T val;
} ez_listnode, *pez_listnode;

/*
 * Use as a list head.
 */
typedef struct _ez_list {
	/* Element list */
	struct _ez_listnode* elms;

  /* The tail node ptr. */
	struct _ez_listnode* tail;

	/* Current count of element in list. */
	int size;

	/* Comparing function between 2 elements. */
	cmp_func cmp;

  /* Clean function for each element. */
	clean_func cls;

	/* Duplication function for each element. */
	dup_func dup;
} ez_list, *pez_list;


/*
 * @1 = circle variable.
 * @2 = list entity.
 * @3 = variable for each element.
 */
#	define foreach_ez_list(_I, _L, _V) \
	for (_I = _L; _V = _I -> val, _I -> next;  \
			_I = _I -> next)

/*
 * Create a List.
 * Return the pointer to the first
 * element if successful,  else 
 * return NULL.
 */
extern pez_list ez_list_create ();

/*
 * Delete the element from the list,
 * if the element doesn't exist, nothing
 * will be done.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
extern void ez_list_del (pez_list, const T);

/*
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

/*
 * Pop head element if existing. No effect if it's empty.
 * $1: List entry ptr.
 */
extern void ez_list_pophead (pez_list);

/*
 * Pop tail element if existing. No effect if list's empty.
 * $1: List entry ptr.
 */
extern void ez_list_poptail (pez_list);

/*
 * Get the head element of list.
 * $1: List entry ptr.
 * Return element. If the list is empty, return NULL.
 */
extern pez_listnode ez_list_gethead (pez_list);

/*
 * Get the tail element of list.
 * $1: List entry ptr.
 * Return element. If the list is empty, return NULL.
 */
extern pez_listnode ez_list_gettail (pez_list);

/*
 * Get the head element of list.
 * $1: List entry ptr.
 * Return element. If the list is empty, return NULL.
 */
extern pez_listnode ez_list_getbyidx (pez_list);

/*
 * Find the first element equalling argument $2,
 * If such an element doesn't exist, return NULL,
 * else return the node.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
extern pez_listnode ez_list_search (pez_list, const T);

/*
 * Find the pre element of the equalling argument $2, 
 * If such element doesn't exist or the front of list 
 * element doesn't exist, return NULL, else return the
 * node.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
extern pez_listnode ez_list_search_pre (pez_list, const T);

/*
 * Find the post element of the equalling argument $2, 
 * If such element doesn't exist or the post of 
 * element doesn't exist, return NULL, else return the
 * node.
 * $1: List entry ptr.
 * $2: Element with type void*.* 
 */
extern pez_listnode ez_list_search_post (pez_list, const T);

/*
 * Return the number of element in the list;
 * NOTE: A new list made by ez_list_create ()
 * will include no element originally.
 */
#	define ez_list_count(__LIST)   \
		((__LIST) ? (__LIST) -> size : 0)

/*
 * Delete all elements in the list.
 * If clean_func is set, then it will be invoked for 
 * each element.
 */
extern void ez_list_del_all (pez_list);

/*
 * Check whether the list is empty.
 * Return true if it is, otherwise 
 * false;
 */
#	define ez_list_isempty(__LIST)   \
		(!! (__LIST) && (__LIST) -> size <= 0)

/*
 * Check whether the element whose value equals $2 is
 * the last element in a list.
 * Return true or false.
 */
extern bool ez_list_islast (const pez_list, const T);

/*
 * Insert an element into list by index.
 * $1 list ptr
 * $2 an element to be inserted.
 * $3 the index at which will be inserted.
 * Return the node ptr if successful, else return NULL.
 */
extern pez_listnode ez_list_pushbyidx (pez_list, const T, int);

/*
 * Insert an element at the end of list. 
 * $1: List ptr.
 * $2: Element value.
 * Return the node ptr if successful, otherwise return NULL.
 */
extern pez_listnode ez_list_pushtail (pez_list, const T);

/*
 * Insert an element in front of the first element.
 * $1: List ptr.
 * $2: The element value.
 * Return true if successful, else return NULL.
 */
extern pez_listnode ez_list_pushhead (pez_list, const T);

/*
 * Release all the memory in list. If its cls_func is set,
 * invoke it for each element.
 * $1: List ptr. If NULL, doing nothing.
 */
extern void ez_list_dispose (pez_list);

/*
 * Duplicate a new list entry from $1.
 * $1: List entry to be copied.
 * Return the list entry if successful. else return NULL.
 */
extern pez_list ez_list_duplicate (pez_list);

/*
 * Reverse list. Nothing will be done if it's empty.
 * $1: List entry ptr.
 * Return $1 forever.
 */
extern pez_list ez_list_reverse (pez_list);

#endif // ~ _EZ_LIST_H_

