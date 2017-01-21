#include "ez_timeutils.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>


/* 
 * Get local date and time. Depends on your local time zone.
 * $1: The return value of type "tm". Current local date and time.
 * $2: Day offset (number of days to go back in the past).
 * Returns value of time in seconds since the Epoch.
 */
time_t get_localtime (struct tm* _ret, int _day_offset) {
	time_t timer;
	struct tm* ltm;

	time (&timer);
	timer -= SEC_PER_DAY * _day_offset;
	ltm = localtime (&timer);

	if (ltm && _ret)
		*_ret = *ltm;
	return timer;
}


/* 
 * Get date and time expressed in UTC.
 * $1: The return value of type "tm". Current local date and time.
 * $2: Day offset (number of days to go back in the past).
 * Returns value of time in seconds since the Epoch.
 */
time_t get_gmtime (struct tm *_ret, int _day_offset) {
	time_t timer;
	struct tm *ltm;

	time (&timer);
	timer -= SEC_PER_DAY * _day_offset;
	ltm = gmtime (&timer);

	if (ltm && _ret)
		*_ret = *ltm;
	return timer;
}

float timediff (const struct timeval* a, const struct timeval* b) {
	float diff;
	diff = ((double) a -> tv_sec * 1.0e6 +
					(double) a -> tv_usec - 
					(double) b -> tv_sec * 1.0e6 -
					(double) b -> tv_usec) / 1.0e6;
	return diff;
}

#if 0
int main (int argc, char* argv []) {
	struct timeval tv1, tv2;

	int i = gettimeofday (& tv1, NULL);
	if (i == -1) {
		printf ("tv1 Error code %d: %s\n", errno, strerror (errno));
	}

	sleep (5);
	i = gettimeofday (& tv2, NULL);
	if (i == -1) {
		printf ("tv2 Error code %d: %s\n", errno, strerror (errno));
	}

	printf ("%f\n", timediff (&tv2, &tv1));

}
#endif

