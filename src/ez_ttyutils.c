#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>


int get_winheight (void) {
	struct winsize win;
	/*
	 * This default value will be used whenever STDOUT
	 * is redirected to a pipe or a file
	 */
	int rows = 3600 * 24;

	if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &win) != -1) {
		if (win.ws_row > 2)
			rows = win.ws_row - 2;
	}
	return rows;
}

#if 0
int main (int argc, char* argv []) {

	int height = get_winheight ();
	printf ("%d\n", height);
	return 0;
}
#endif

