#include "ez_cpu.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#	define LINE_LEN 10

/*
 * Get the number of CPU for your machine.
 * Return -1 if an error occurred.
 */
int count_cpus (void) {
	FILE *fp;
	char value [LINE_LEN];
	int ret = 0;
	unsigned int cpunr = 0;

	fp = fopen ("/proc/stat", "r");
	if (!fp) return -1;

	while (!feof (fp)) {
		if (!fgets (value, LINE_LEN, fp))
			continue;
		value [LINE_LEN - 1] = '\0';
		if (strlen (value) < (LINE_LEN - 2))
			continue;
		if (strstr (value, "cpu "))
			continue;
		if (sscanf (value, "cpu%d ", &cpunr) != 1)
			continue;
		if (cpunr > ret)
			ret = cpunr;
	}
	fclose (fp);

	/* cpu count starts from 0, on error return -1 (UP) */
	return (ret + 1);
}

#if 0
int main (int argc, char* argv []) {
	printf ("CPU number = %d", count_cpus ());
	return 0;
}
#endif

