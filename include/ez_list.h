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

typedef struct _node* _position;
typedef struct _node* _list;

/*
   Delete the element from list,
   if the element doesn't exist, nothing
   will be done.
*/
extern void ez_list_del (_list, _element);

/*
   Find the first element equaling argument @2,
   If such element doesn't exist, return NULL,
   else return position.
*/
extern _position ez_list_find (_list, _element);

/*
   Find the pre element of the equaling 
   argument @2, If such element doesn't 
   exist or the front of list element 
   equals @2, return NULL, else return 
   its position.
*/
extern _position 
ez_list_find_pre (_list, _element);

extern _list ez_list_create ();
extern void ez_list_del_all (_list);
extern bool ez_list_empty (_list);
extern bool ez_list_islast (_list, _position);
extern bool ez_list_insert (_list, _element, _position);
extern bool ez_list_insert_real (_list, _element);

#endif // ~ __cplusplus


#endif // ~ _EZ_LIST_H_
