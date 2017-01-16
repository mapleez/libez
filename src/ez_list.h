/*
	author : ez
	date : 2015/5/21
	describe : The linked list declaration.
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

	/* Current count of element in list. */
	int size;

	/* Comparing function between 2 elements. */
	cmp_func cmp;

  /* Clean function for each element. */
	clean_func cls;
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
 * Find the first element equalling argument $2,
 * If such an element doesn't exist, return NULL,
 * else return the node.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
extern pez_listnode ez_list_find (pez_list, const T);

/*
 * Find the pre element of the equalling argument $2, 
 * If such element doesn't exist or the front of list 
 * element doesn't exist, return NULL, else return the
 * node.
 * $1: List entry ptr.
 * $2: Element with type void*.
 */
extern pez_listnode ez_list_find_pre (pez_list, const T);

/*
 * Return the number of element in the list;
 * NOTE: A new list made by ez_list_create ()
 * will include no element originally.
 */
extern int ez_list_count (const pez_list);

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
extern bool ez_list_empty (const pez_list);

/*
 * Check whether the position is
 * the last element in a list.
 * Return true or false.
 */
extern bool ez_list_islast (const pez_list, const T);

/*
 * Insert an element into list.
 * $1 list ptr
 * $2 an element to be inserted.
 * $3 the position that will be inserted ahead.
 * Return the node ptr if successful, else return NULL.
 */
extern pez_node ez_list_insert (pez_list, const T, int idx);

/*
 * Insert an element at the end of list. 
 * $1: List ptr.
 * $2: Element value.
 * Return the node ptr if successful, otherwise return NULL.
 */
extern pez_node ez_list_insert_real (pez_list, const T);

/*
 * Insert an element in front of the first element.
 * $1: List ptr.
 * $2: The element value.
 * Return true if successful, else return NULL.
 */
extern pez_node ez_list_insert_head (pez_list, const T);

/*
 * Release all the memory in list. If its cls_func is set,
 * invoke it for each element.
 * $1: List ptr. If NULL, doing nothing.
 */
extern void ez_list_dispose (pez_list);

/*
 * Reverse list. Nothing will be done if it's empty.
 * $1: List entry ptr.
 * Return $1 forever.
 */
extern pez_list ez_list_reverse (pez_list);

#endif // ~ _EZ_LIST_H_

