#ifndef _EZ_SOCKCLIENT_H_
#	define _EZ_SOCKCLIENT_H_

#include "ez.h"
#include "ez_sock.h"

typedef class ez_sockclient {

private:
	ez_inet_sock _sock;
	ez_inet_sock _srv;
public:
	ez_sockclient (pez_inet_sock, pez_inet_sock);
	ez_sockclient ();
	ez_sockclient (char*, int, char* int);

	void set_server (const char*, const int);
	void set_sock (const char*, const int);

	void dispose_client ();

	int open ();
	bool close ();
	int read (bytes, int, int);
	int write (bytes, int);

}* pez_sockclient;



class sock_except {
	private:
		int _err_code;
		char* _err_msg;
		int _sockfd;
	public:
		sock_except (int, int);
		sock_except (const char*);
		void set_err_msg (const char*);
};


#endif // ~ _EZ_SOCKCLIENT_H_
