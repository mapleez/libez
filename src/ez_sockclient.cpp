#include "ez_sockclient.h"
#include "ez_sock.h"
#include <stdlib.h>
#include <iostream>
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
}

ez_sockclient :: ez_sockclient () {
	// this -> _srv = ez_create_inet_sock ("", 0);
	// this -> _sock = ez_create_inet_sock ("", 0);
}

ez_sockclient :: ez_sockclient (
	char* _srv_ip, int _srv_port,
	char* _client_ip, int _client_port) {
	this -> _srv = 
		ez_create_inet_sock (_srv_ip, _srv_port);
	this -> _sock = 
		ez_create_inet_sock (_client_ip, _client_port);
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
	if (! this -> _srv -> _addr) {
		this -> _srv -> _addr = (struct sockaddr*) 
			malloc (sizeof (struct sockaddr));
	}
	// TODO...



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
	return 
		shutdown (this -> _srv -> _sockfd, _flag);
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

#if 1

int 
main (int argc, char* argv []) {
	pez_sockclient client = new ez_sockclient;
	client -> set_server ("10.14.4.167", 5556);
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

	return 0;
}


#endif // ~  debug

