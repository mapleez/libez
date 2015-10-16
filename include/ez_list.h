/*
	author : ez
	date : 2015/5/21
	describe : the list ADT
*/

#ifndef _EZ_LIST_H_
#	define _EZ_LIST_H_

#include <stdbool.h>

#	define _element int
#	define _elm_size (sizeof (_element))

struct _node {
	_element val;
	struct _node* next;
};

#	define _list_size  (sizeof (struct _node))


typedef struct _node* _position;
typedef struct _node* _list;


extern void del (_list, _element);
extern _position find (_list, _element);
extern _position find_pre (_list, _element);
extern _list create_list ();
extern void del_all (_list);
extern bool empty (_list);
extern bool islast (_list, _position);
extern bool insert (_list, _element, _position);
extern bool insert_real (_list, _element);


#endif // ~ _EZ_LIST_H_
