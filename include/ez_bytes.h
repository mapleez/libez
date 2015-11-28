#ifndef _EZ_BYTES_H_
# define _EZ_BYTES_H_

/*
 * author : ez
 * date : 2015/11/26
 * describe : algorithm for bytes sequence.
*/

#include "ez.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int
ez_bytes_index_sep (bytes, bytes, int, int);

// returns the first index in byte sequence.
// return -1 if error or @2 cannot be found
// in @1
extern int
ez_bytes_index_byte (bytes, byte, int);

// returns the number of bytes @2 apparance in @1
// return -1 if error, return 0 if there is
// no one.
extern int
ez_bytes_count_bytes (bytes, bytes, int, int);

// reports whether the bytes @2 == @1
extern bool
ez_bytes_equal_sep (bytes, bytes, int, int);


extern bool 
ez_bytes_hasprefix (bytes, bytes, int, int);


extern bool 
ez_bytes_hassuffix (bytes, bytes, int, int);

#ifdef __cplusplus
}
#endif

#endif // ~ _EZ_BYTES_H_
