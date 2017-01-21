#ifndef _EZ_DEVUTILS_H_
#	define _EZ_DEVUTILS_H_

#include <stdbool.h>

#	define SYSFS_USBDEV  "/sys/bus/usb/devices"
#	define SYSFS_BLOCK   "/sys/block"

#	define DISKSTAT      "/proc/diskstat"

extern int get_usbdev_num (void);

extern int get_diskdev_num (bool, bool);

#endif // ~ _EZ_DEVUTILS_H_
