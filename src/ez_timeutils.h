#ifndef _EZ_TIMEUTILS_H_
#	define _EZ_TIMEUTILS_H_

#include <time.h>

#	define SEC_PER_DAY (3600 * 24)

/* 
 * Get local date and time.
 * $1: The return value of type "tm". Current local date and time.
 * $2: Day offset (number of days to go back in the past).
 * Returns value of time in seconds since the Epoch.
 */
extern time_t get_localtime (struct tm*, int);


/* 
 * Get date and time expressed in UTC.
 * $1: The return value of type "tm". Current local date and time.
 * $2: Day offset (number of days to go back in the past).
 * Returns value of time in seconds since the Epoch.
 */
extern time_t get_gmtime (struct tm *, int);

#endif // ~ _EZ_TIMEUTILS_H_

