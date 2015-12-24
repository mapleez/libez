#ifndef _EZ_H_

#	define _EZ_H_
#include <stdio.h>
#include <stdint.h>

#ifndef NULL
#	define NULL ((void*) 0)
#endif // ~ NULL

#	define __xstr(___s) __str (___s)
#	define __str(___s) #___s

#	define println(___s) \
		printf ("%s\n", ___s)

#ifdef __GNUC__
// depend with byte order
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#	define tobigend16(___D)  (((uint16_t)((___D) & 0xff00) >> 8) | ((uint16_t)((___D) & 0x00ff) << 8))
#	define tolittleend16(___D) (___D)

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

#	define tolittleend16(___D)  (((uint16_t)((___D) & 0xff00) >> 8) | ((uint16_t)((___D) & 0x00ff) << 8))
#	define tobigend16(___D)  (___D)
#endif

#endif // ~ __GNUC__

#	define BIGGER	(-1)
#	define EQUAL  	(0)
#	define SMALLER  (1)

#	define ORDER_DESC     (true)
#	define ORDER_ASC	  (false)

typedef uint8_t* bytes;
typedef uint8_t  byte;

typedef int (*cmp_func)(const void*, const void*);

#	define BASIC_SWAP(___A, ___B) \
		do {  \
			(___A) ^= (___B);  \
			(___B) ^= (___A);  \
			(___A) ^= (___B);  \
		} while (0)

#endif // ~ _EZ_H_

