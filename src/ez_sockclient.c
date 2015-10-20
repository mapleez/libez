#include "ez_sockclient.h";
#include <winsock2.h>

ez_sockclient :: ez_sockclient (
		pez_inet_sock _srv,
		pez_inet_sock _client)
{
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
		// TODO...
	}
}

void ez_sockclient :: set_sock (
	const char* _ip, const int _port) {
}

void ez_sockclient :: dispose_client () {
}

int ez_sockclient :: open () {
}

bool ez_sockclient :: close () {
}

int ez_sockclient :: read (
		bytes _buf, int _len, int _flag) {
}

int ez_sockclient :: write (
		bytes _buf, int _len) {
}

