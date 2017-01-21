#include "ez.h"
#include "ez_devutils.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <unistd.h>

static int __is_device (char*, int);

static int __is_device (char* name, int allow_virtual) {
	char syspath [256];
	char *slash;

	/* Some devices may have a slash in their 
	   name (eg. cciss/c0d0...) */
	while ((slash = strchr (name, '/')))
		*slash = '!';
	snprintf (syspath, sizeof (syspath), "%s/%s%s", 
		SYSFS_BLOCK, name, allow_virtual ? "" : "/device");

	return !(access (syspath, F_OK));
}

/* 
 * Count number of USB devices in /sys/bus/usb/devices.
 * Don't count USB root hubs.
 * Returns Number of USB devices plugged into the system.
 * Return -1 if directory doesn't exist in sysfs.
 */
int get_usbdev_num (void) {
	DIR *dir;
	struct dirent *drd;
	int usbn = 0;

	if ((dir = opendir (SYSFS_USBDEV)) == NULL)
		return -1;

	/* Get current file entry */
	while ((drd = readdir (dir)) != NULL) {
		if (isdigit (drd -> d_name [0]) && 
				! strchr (drd -> d_name, ':')) usbn ++;
	}

	closedir (dir);

	return usbn;
}

// TODO...
int get_diskdev_num (bool _disk_only, bool _only_used) {
	FILE *fp;
	char line [256];
	char dev_name [1024];
	int dev = 0, i;
	unsigned long rd_ios, wr_ios;

	if ((fp = fopen (DISKSTAT, "r")) == NULL)
		/* File non-existent */
		return 0;

	/*
	 * Counting devices and partitions is simply a matter of counting
	 * the number of lines...
	 */
	while (fgets (line, sizeof (line), fp) != NULL) {
		/* Only disk should be count. */
		if (! _disk_only) {
			i = sscanf (line, "%*d %*d %s %lu %*u %*u %*u %lu",
				   dev_name, &rd_ios, &wr_ios);
			if ((i == 2) || 
					! __is_device (dev_name, 1))
				/* It was a partition and not a device */
				continue;
			if (_only_used && !rd_ios && !wr_ios)
				/* Unused device */
				continue;
		}
		dev ++;
	}

	fclose (fp);

	return dev;
}

#if 1
int main (int argc, char* argv []) {
	int num = get_diskdev_num (0, 0); // get_usbdev_num ();
	printf ("DISK number = %d\n", num);
	
	return 0;
}
#endif

