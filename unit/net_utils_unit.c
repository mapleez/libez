#include "ez.h"
#include "ez_netutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main (int argc, char* argv []) {

	in_addr_t addr =  -1;

	if (argc <= 1) {
		println ("Input hostname!");
		exit (0);
	}
	addr = host_resolv (argv [1]);
	printf ("%d.%d.%d.%d (%d)\n", 
			(addr & 0xff000000) >> 24,
			(addr & 0x00ff0000) >> 16,
			(addr & 0x0000ff00) >>  8,
			(addr & 0x000000ff), addr);
	
	return 0;
}
