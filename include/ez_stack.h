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
#	define _stk_size   (sizeof (struct _stk))

struct _stk {
	int capacity;
	int sp;
	_tp* array;	
};

typedef struct _stk* _stack;


extern bool empty_stk (_stack);
extern bool full_stk (_stack);
extern _stack create_stack (int);
extern void dispose_stack (_stack);
extern void clear_stack (_stack);
extern bool push (_stack, _tp);
extern bool pop (_stack);
extern _tp top (_stack);
extern _tp topandpop (_stack);
#ifdef __debug__

extern void show (_stack);

#endif // ~ __debug__


#endif // ~ _EZ_STACK_H_
