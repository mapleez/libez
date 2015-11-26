#ifndef _EZ_BYTES_H_
# define _EZ_BYTES_H_

#include "ez.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int
ez_bytes_index_sep (bytes, bytes, int, int);

// returns the first byte in byte sequence.
extern int
ez_bytes_index_byte (bytes, byte, int);

// reports whether the bytes @2 == @1
extern int
ez_bytes_equal_sep (bytes, bytes, int, int);


#ifdef __cplusplus
}
#endif

#endif // ~ _EZ_BYTES_H_
