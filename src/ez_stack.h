/*
	author : ez
	date : 2015/5/19
	describe : stack declaration
*/

#ifndef _EZ_STACK_H_
#	define _EZ_STACK_H_

#include <stdbool.h>
#include "ez.h"

#	define STACK_EMPTY_MARK  -1
#	define DEF_STACK_CAPACITY  32

#	define EZ_STACK_SIZE (sizeof (struct _ez_stack))

typedef struct _ez_stack {

	/* Total capacity */
	int capacity;

	/* Current index of array holding elements. 
	 * It's -1 when the stack is created or cleaned.
	 */
	int sp;

	/* We use a void ptr to 
	 * store an element in stack. */
	T* array; 

	/* A function to clean each element.
	 * The function will be invoke while 
	 * some element is removed from stack. 
	 * e.g. dispose () will remove and 
	 * call it for them each element. 
	 * And if the function is NULL, it will
	 * not be invoked. */
	clean_func cls;
} ez_stack, *pez_stack;


/*
 * Check whether the stack is empty or not.
 * $1: stack entry, a ptr. If ptr is NULL, false will be returned.
 * Return true (1) if it's empty. Or false (0)
 */
#	define ez_stack_empty(__S)   \
		(!!(__S) && (__S) -> sp == STACK_EMPTY_MARK)

/*
 * Check whether the stack is full or not.
 * $1: stack entry, a ptr. If ptr is NULL, false will be returned.
 * Return true (1) if it's full. Or false (0)
 */
#	define ez_stack_full(__S)    \
		(!!(__S) && (__S) -> sp + 1 == (__S) -> capacity)

/*
 * Create an empty stack with the original capacity.
 * $1: The original capacity of stack.
 * Return the entry ptr if successful. Or NULL will be returned.
 */
extern pez_stack ez_stack_create (int);

/*
 * Dispose the stack entry. If the input ptr is NULL. Nothing 
 * will be done.
 * $1: stack entry, a ptr.
 */
extern void ez_stack_dispose (pez_stack);

/*
 * Dispose the stack entry. If the input ptr is NULL. Nothing 
 * will be done.
 * $1: stack entry, a ptr.
 */
extern void ez_stack_clear (pez_stack);

/*
 * Push an element into stack. If the input stack ptr or
 * element ptr is NULL, nothing will be done and return NULL.
 * $1: Stack entry ptr.
 * $2: Element entry ptr.
 * Return current element if successful. Otherwise return NULL.
 */
extern T ez_stack_push (pez_stack, const T);

/*
 * Pop and remove it from stack. If the input 
 * stack ptr is NULL, false returned. Note if clean function 
 * is registered, it will be invoked to handle this element.
 * $1: Stack entry ptr.
 * Return true if successful. Otherwise return false.
 */
extern bool ez_stack_pop (pez_stack);

/*
 * Return top element.
 * $1: Stack entry ptr.
 * Return element ptr.
 */
extern T ez_stack_top (pez_stack);

/*
 * Return top element and remove it. But the clean function 
 * shell not be invoked no metter what it has been set.
 * $1: Stack entry ptr.
 * Return element ptr. If the stack is empty or $1 is NULL, 
 * NULL will be returned.
 */
extern T ez_stack_topandpop (pez_stack);

#ifdef __debug__
extern void show (pez_stack);
#endif // ~ __debug__


#endif // ~ _EZ_STACK_H_
