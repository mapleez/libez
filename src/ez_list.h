/*
	author : ez
	date : 2015/5/21
	describe : the list ADT
*/

#ifndef _EZ_LIST_H_
#	define _EZ_LIST_H_



#ifndef __cplusplus
#include <stdbool.h>

#	define _element int
#	define _elm_size (sizeof (_element))

struct _node {
	struct _node* next;
	_element val;
};

#	define _list_size  (sizeof (struct _node))
#	define _node_size  _list_size

/*
 * @1 = circle variable.
 * @2 = list entity.
 * @3 = variable for each element.
 */
#	define foreach_ez_list(_I, _L, _V) \
	for (_I = _L; _V = _I -> val, _I -> next;  \
			_I = _I -> next)

typedef struct _node* _position;
typedef struct _node* _list;

/*
   Delete the element from list,
   if the element doesn't exist, nothing
   will be done.
*/
extern void 
ez_list_del (_list, const _element);

/*
   Find the first element equaling argument @2,
   If such element doesn't exist, return NULL,
   else return position.
*/
extern _position 
ez_list_find (_list, const _element);

/*
   Find the pre element of the equaling 
   argument @2, If such element doesn't 
   exist or the front of list element 
   equals @2, return NULL, else return 
   its position.
*/
extern _position 
ez_list_find_pre (_list, const _element);

/*
   Return the number of element 
   in the list;

   NOTE: A new list made by ez_list_create ()
   will include one element originally.
*/
extern int
ez_list_count (const _list);

/*
   Create a List,

   return the pointer to the first
   element if successful,  else 
   return NULL.
*/
extern _list ez_list_create ();


/*
   Delete all elements in the list.
   The @1 will be set to NULL;
*/
extern void ez_list_del_all (_list);

/*
   Check whether the list is empty.
   return true if it is, otherwise 
   false;

   WARNING: because of the header of list,
   each created list will include at least
   one element, so in this version, the 
   function always return true.
*/
extern bool ez_list_empty (const _list);

/*
   Check whether the position is
   the last element in a list.

   return true or false.
*/
extern bool 
ez_list_islast (const _list, const _position);

/*
   Insert an element into list.
   @1 list ptr
   @2 an element to be inserted.
   @3 the position that will be inserted ahead.

   return true if successful, else return false;
*/
extern bool 
ez_list_insert (_list, const _element, _position);


/*
   Insert an element at the end of list.
   Return true if successful, otherwise
   return false.
*/
extern bool 
ez_list_insert_real (_list, const _element);

/*
   Insert an element at the top of list.
   Return true if successful, else return
   false.
*/
extern bool 
ez_list_insert_top (_list*, const _element);


extern _list 
ez_list_reverse (_list);

#endif // ~ __cplusplus


#endif // ~ _EZ_LIST_H_
