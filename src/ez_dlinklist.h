#ifndef _EZ_DLINKLIST_H_
#	define _EZ_DLINKLIST_H_

#include "ez.h"

#ifndef DBG
#	define DBG
#endif // ~ DBG

typedef struct dlist_elm dlist_elm, * pdlist_elm;
typedef struct ez_dlist ez_dlist, * pez_dlist;
typedef void (*free_func) (void*);
typedef void* (*dup_func) (void*);

// each element in the list.
struct dlist_elm {
	pdlist_elm _next;
	pdlist_elm _prev;
	void* _value;
};

// list entity;
struct ez_dlist {
	pdlist_elm _head;
	pdlist_elm _tail;
	int _count;
	cmp_func _match;
	free_func _free;
	dup_func _dup;
};

#	define SIZE_EZ_DLIST (sizeof (struct ez_dlist))
#	define SIZE_EZ_DLIST_ELM (sizeof (struct dlist_elm))

#	define set_dlist_match(___L, ___F) (___L) -> _match = (___F)
#	define set_dlist_free(___L, ___F) (___L) -> _free = (___F)
#	define set_dlist_dup(___L, ___F) (___L) -> _dup = (___F)

extern pez_dlist ez_dlist_create (void);
extern void ez_dlist_dispose (pez_dlist*);
extern pdlist_elm ez_dlist_gethead (pez_dlist);
extern pdlist_elm ez_dlist_gettail (pez_dlist);
extern pez_dlist ez_dlist_duplicate (const pez_dlist);
extern pdlist_elm ez_dlist_pushhead (pez_dlist, void* const);
extern pdlist_elm ez_dlist_pushtail (pez_dlist, void* const);
extern void ez_dlist_pophead (pez_dlist);
extern void ez_dlist_poptail (pez_dlist);
extern pdlist_elm ez_dlist_search (pez_dlist, void* const);
extern pdlist_elm ez_dlist_getbyidx (pez_dlist, int);

#ifdef DBG
typedef void (*disp_each) (pdlist_elm);
extern void display_dlist_head (pez_dlist, disp_each);
extern void display_dlist_tail (pez_dlist, disp_each);
#endif

#endif // ~ _EZ_DLINKLIST_H_

