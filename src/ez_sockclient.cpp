#include "ez_sockclient.h"
#include <string.h>
#include "ez_sock.h"
#include <stdlib.h>
#include <iostream>
#include <errno.h>
// #include <string.h>

#ifdef _MSC_VER

#include <winsock2.h>

#elif  defined __GNUC__

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#endif // ~ __GNUC__

using namespace std;

ez_sockclient :: ez_sockclient (
		pez_inet_sock _srv,
		pez_inet_sock _client)
{
	this -> _srv = _srv;
	this -> _sock = _client;
	this -> _srv -> _sockfd = 
		socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

ez_sockclient :: ez_sockclient () {
	this -> _srv = ez_create_inet_sock ("", 0);
	this -> _sock = ez_create_inet_sock ("", 0);
	this -> _srv -> _sockfd = 
		socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

ez_sockclient :: ez_sockclient (
	char* _srv_ip, int _srv_port,
	char* _client_ip, int _client_port) {
	this -> _srv = 
		ez_create_inet_sock (_srv_ip, _srv_port);
	this -> _sock = 
		ez_create_inet_sock (_client_ip, _client_port);
	this -> _srv -> _sockfd = 
		socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void ez_sockclient :: set_server (
	const char* _ip, const int _port) {
	if (! this -> _srv) {
		this -> _srv = 
			ez_create_inet_sock (_ip, _port);
	} else {
		this -> _srv -> _port = _port;
		this -> _srv -> _ip._ip_i = 
			inet_addr (_ip);
	}
}

void ez_sockclient :: set_sock (
	const char* _ip, const int _port) {
	if (! this -> _sock) {
		this -> _sock = 
			ez_create_inet_sock (_ip, _port);
	} else {
		this -> _sock -> _port = _port;
		this -> _sock -> _ip._ip_i = 
			inet_addr (_ip);
	}
}

void ez_sockclient :: client_dispose () {
	if (this -> _sock) 
		ez_dispose_inet_sock (this -> _sock);
	if (this -> _srv)
		ez_dispose_inet_sock (this -> _srv);
	this -> _srv = this -> _sock = NULL;
}

// call connect ()
bool
ez_sockclient :: client_open () {
	struct sockaddr_in * ptr = NULL;
	if (! this -> _srv -> _addr) {
		this -> _srv -> _addr = (struct sockaddr*) 
			malloc (sizeof (struct sockaddr));
	}
	ptr = (struct sockaddr_in*) this -> _srv -> _addr;
	// this -> _srv -> _addr -> sin_family = AF_INET;
	ptr -> sin_family = AF_INET;

	// this -> _srv -> _addr -> sin_addr.s_addr = 
	ptr -> sin_addr.s_addr = 
		this -> _srv -> _ip._ip_i; // IP

	// this -> _srv -> _addr -> sin_port = 
	ptr -> sin_port = 
		htons (this -> _srv -> _port); // PORT

	return 
		0 == connect (this -> _srv -> _sockfd, 
				this -> _srv -> _addr,
			 sizeof (struct sockaddr));
}

inline bool 
ez_sockclient :: client_close () {
	// if successful, return 0;
	return 
		close (this -> _srv -> _sockfd) == 0;
}

inline bool 
ez_sockclient :: client_shutdown (int _flag) {
	// 0 if successful , else return -1
	return 
		0 == shutdown (this -> _srv -> _sockfd, _flag);
}

inline int 
ez_sockclient :: client_read (
	bytes _buf, int _len, unsigned int _flag = 0) {
	return
		recv (this -> _srv -> _sockfd, _buf,
				_len, _flag);
}

inline int 
ez_sockclient :: client_write (
	bytes _buf, int _len) {
	return 
		send (this -> _srv -> _sockfd,
			  _buf, _len, 0);
}

#if 0

int 
main (int argc, char* argv []) {
#if 1 
	pez_sockclient client = new ez_sockclient;
	client -> set_server ("42.121.69.11", 80);
	if (! client -> client_open ()) {
		cout << "error in open socket" << endl;
		client -> client_dispose ();
		delete client;
		client = NULL;
		return 0;
	}

	if (! client -> client_shutdown (SHUT_RDWR)) {
		cout << "error in shutdown socket" << endl;
		client -> client_dispose ();
		delete client;
		client = NULL;
		return 0;
	}
#endif

#if 0
	int sock = 0;
	int res = 0;
	// struct sockaddr addr;
	struct sockaddr_in ptr/* = (struct sockaddr_in*) &addr*/;
	uint16_t port = 23;
	sock = socket (AF_INET, SOCK_STREAM, 0);
	bzero (&ptr, sizeof (ptr));
	if (sock == -1) {
		printf ("error in create socket\n");
	}

	ptr.sin_family = AF_INET;
	ptr.sin_port = htons (port);
	ptr.sin_addr.s_addr = (inet_addr ("10.14.4.167"));
	// res = inet_pton (AF_INET, "10.14.4.167", &ptr.sin_addr);

	if (-1 == connect (sock, (struct sockaddr*) &ptr, sizeof (ptr))) {
		printf ("error in connect socket\n%d", errno);
	}

	shutdown (sock, SHUT_RDWR);
#endif 
	return 0;
}


#endif // ~  debug

