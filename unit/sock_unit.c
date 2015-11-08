#include "internet/ez_channel.h"
// #include "internet/ez_endpoint.h"

int main (int argc, char* argv []) {
	int res = 0;
	pez_channel chan = ez_init_channel ("10.14.4.167", 21);
	res = ez_open_channel (chan);

	// char* ptr = ez_addr_to_string (,);
	// printf ("%s\n", ptr);
	// int ipaddr = 0;
	// int res = 0;
	// unsigned char* ptr = '\0';
	// res = ez_stringaddr_to_int (&ipaddr, "....");

	// if (ptr != '\0');
	return 0;
}
