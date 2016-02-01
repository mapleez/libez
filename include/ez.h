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

#	define BASIC_SWAP(___A, ___B) \
		do {  \
			(___A) ^= (___B);  \
			(___B) ^= (___A);  \
			(___A) ^= (___B);  \
		} while (0)

#ifdef __GNUC__
// depend with byte order
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
// 16 bits
#	define tobigend16(___D)  (((uint16_t)((___D) & 0xff00) >> 8) | ((uint16_t)((___D) & 0x00ff) << 8))
#	define tolittleend16(___D) (___D)
#	define tolocalend16(___D)  tolittleend16 (___D)

// 32 bits
#	define tobigend32(___D)  memrev32 (___D)
#	define tolittleend32(___D) (___D)
#	define tolocalend32(___D)  tolittleend32 (___D)

// 64 bits
#	define tobigend64(___D)  memrev64 (___D)
#	define tolittleend64(___D)  (___D)
#	define tolocalend64(___D)  tolittleend64 (___D)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
// 16 bits
#	define tolittleend16(___D)  (((uint16_t)((___D) & 0xff00) >> 8) | ((uint16_t)((___D) & 0x00ff) << 8))
#	define tobigend16(___D)  (___D)
#	define tolocalend16(___D) tobigend16 (___D)

// 32 bits
#	define tolittleend32(___D)  memrev32 (___D)
#	define tobigend32(___D) (___D)
#	define tolocalend32(___D)  tobigend32 (___D)

// 64 bits
#	define tobigend64(___D)  (___D)
#	define tolittleend64(___D)  memrev64 (___D)
#	define tolocalend64(___D)  tobigend64 (___D)
#endif

#endif // ~ __GNUC__

// for malloc () memory aligment
#if defined (__sun) || defined (__sparc) || defined (__sparc__)
#	define MEM_PREFIX (sizeof (long long))
#else
#	define MEM_PREFIX (sizeof (size_t))
#endif

#	define BIGGER	(-1)
#	define EQUAL  	(0)
#	define SMALLER  (1)

#	define ORDER_DESC     (true)
#	define ORDER_ASC	  (false)

typedef uint8_t* bytes;
typedef uint8_t  byte;

typedef int (*cmp_func)(const void*, const void*);

static inline uint32_t memrev32 (uint32_t _dat) {
	uint8_t* ptr = (uint8_t*) &_dat;
	BASIC_SWAP (ptr [0], ptr [3]);
	BASIC_SWAP (ptr [1], ptr [2]);
	return _dat;
}

static inline uint64_t memrev64 (uint64_t _dat) {
	uint8_t* ptr = (uint8_t*) &_dat;
	BASIC_SWAP (ptr [0], ptr [7]);
	BASIC_SWAP (ptr [1], ptr [6]);
	BASIC_SWAP (ptr [2], ptr [5]);
	BASIC_SWAP (ptr [3], ptr [4]);
	return _dat;
}

#endif // ~ _EZ_H_

