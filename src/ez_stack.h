/*
	author : ez
	date : 2015/5/19
	describe : stack declaration

*/

#ifndef _EZ_STACK_H_
#	define _EZ_STACK_H_

#include <stdbool.h>
#	define EMPTY_MARK  -1

#	define __debug__

#	define _tp int
#	define _tp_size   (sizeof (_tp))
#	define _stk_size   (sizeof (struct _ez_stack))

typedef struct _ez_stack {
	int capacity;
	int sp;
	_tp* array;	
} ez_stack,
	*pez_stack;
// typedef struct _ez_stack* pez_stack;

extern bool ez_stack_empty (pez_stack);
extern bool ez_stack_full (pez_stack);
extern pez_stack ez_stack_create (int);
extern void ez_stack_dispose (pez_stack);
extern void ez_stack_clear (pez_stack);
extern bool ez_stack_push (pez_stack, _tp);
extern bool ez_stack_pop (pez_stack);
extern _tp ez_stack_top (pez_stack);
extern _tp ez_stack_topandpop (pez_stack);

#ifdef __debug__
extern void show (pez_stack);
#endif // ~ __debug__


#endif // ~ _EZ_STACK_H_
