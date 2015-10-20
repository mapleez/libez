#ifndef _EZ_H_

#	define _EZ_H_
#include <stdio.h>
#include <stdint.h>

#ifndef NULL
#	define NULL ((void*) 0)
#endif // ~ NULL

#	define println(___s) \
		printf ("%s\n", ___s)

#	define BIGGER	(-1)
#	define EQUAL  	(0)
#	define SMALLER  (1)

#	define ORDER_DESC     (true)
#	define ORDER_ASC	  (false)


typedef int (*cmp_func)(const void*, const void*);

#	define BASIC_SWAP(___A, ___B) \
		do {  \
			(___A) ^= (___B);  \
			(___B) ^= (___A);  \
			(___A) ^= (___B);  \
		} while (0)

#endif // ~ _EZ_H_

