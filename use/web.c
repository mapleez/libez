#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "internet/ez_socktools.h"
#include "ez_log.h"
#include "ez_event.h"
#include "ez.h"

#	define SBUF_SIZE 4 
#	define RBUF_SIZE 4096

#	define BAIDU "www.baidu.com"
#	define NCEPU "www.ncepu.edu.cn"

// baidu, ncepu
byte __rcv_datas1 [RBUF_SIZE] = {0, };
byte __rcv_datas2 [RBUF_SIZE] = {0, };

byte __sent_datas [RBUF_SIZE] = {0, };
byte __sent_frm [RBUF_SIZE] = 
"Host: github.com\r\n"
"User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0 Iceweasel/31.8.0\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"Accept-Language: en-US,en;q=0.5\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Cookie: logged_in=no; _octo=GH1.1.900663949.1453280510; _ga=GA1.2.243619504.1453280510; _gat=1; _gh_sess=eyJzZXNzaW9uX2lkIjoiNmMxZmNlZTU1YjAxY2IzOWRlMzEwMjI4NGRkZTNjNTkiLCJfY3NyZl90b2tlbiI6Inc5WG5UUTNwcSt6ZDZncFpCVk1JUGY5TGpnRTcyV1c3Zi9xSkVzQzFEVTA9In0%3D--6d600c4bcea301270e8f88d14f88f583944cf3d5; tz=Europe%2FLondon\r\n"
"Connection: keep-alive\r\n";

pez_logger logger;
pezevent_loop loop;

static void sock_readable (pezevent_loop, int, int, void*);
static void sock_writable (pezevent_loop, int, int, void*);

int main (int argc, char* argv []) {

	int baidu, ncepu;
	int tmp;
	struct in_addr* addr;
	struct sockaddr_in sockaddr;
	logger = ez_logger_new (NULL, NULL, 
			LOGTYPE_CONSOLE, NULL);

	ez_logger_info (logger, "start init event loop.");
	loop = ezevent_create_eventloop (32);

	ez_logger_info (logger, "start init sockets.");
	baidu = socket (AF_INET, SOCK_STREAM, 0);
	ncepu = socket (AF_INET, SOCK_STREAM, 0);

	// get baidu addr
	if (! (addr = ez_hostnameto_sockaddr (BAIDU))) {
		ez_logger_notice (logger, "error getting " BAIDU " IP address");
		return 0;
	}

	// connect BAIDU
	ez_logger_notice (logger, "successful in getting " BAIDU " IP address");
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = tobigend16 (80);
	// memcpy (&sockaddr.sin_addr, addr, sizeof (*addr));
	*(uint32_t*) &sockaddr.sin_addr = (*(uint32_t*) addr);
	// if (connect (baidu, (struct sockaddr*) &sockaddr, sizeof (struct sockaddr)) == -1) {
	// 	ez_logger_error (logger, "error connect " BAIDU);
	// 	return 0;
	// }
	ez_logger_notice (logger, "connect " BAIDU " successful");

	// get ncepu addr
	if (! (addr = ez_hostnameto_sockaddr (NCEPU))) {
		ez_logger_notice (logger, "error getting " NCEPU " IP address");
		return 0;
	}

	// connect NCEPU
	ez_logger_notice (logger, "successful in getting " NCEPU " IP address");
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = tobigend16 (80);
	// memcpy (&sockaddr.sin_addr, addr, sizeof (*addr));
	*(uint32_t*) &sockaddr.sin_addr = (*(uint32_t*) addr);
	// if (connect (ncepu, (struct sockaddr*) &sockaddr, sizeof (struct sockaddr)) == -1) {
	// 	ez_logger_error (logger, "error connect " NCEPU);
	// 	return 0;
	// }
	ez_logger_notice (logger, "connect " NCEPU " successful");

	if (baidu == -1 || ncepu == -1)
		ez_logger_error (logger, "error in initializing sockets.");

	if (ezevent_add_fileevent (loop, baidu, EE_READABLE, 
					sock_readable, __rcv_datas1) == RTNVAL_SUCC &&
			ezevent_add_fileevent (loop, ncepu, EE_READABLE,
					sock_readable, __rcv_datas2) == RTNVAL_SUCC &&
			ezevent_add_fileevent (loop, baidu, EE_WRITABLE,
					sock_writable, __sent_frm) == RTNVAL_SUCC &&
			ezevent_add_fileevent (loop, ncepu, EE_WRITABLE,
					sock_writable, __sent_frm) == RTNVAL_SUCC)
		ez_logger_info (logger, "socket added into loop.");
	else
		ez_logger_error (logger, "error.");

	// send first frame
	tmp = send (baidu, __sent_frm, RBUF_SIZE, 0);
	ez_logger_notice (logger, "sent %d datas to " BAIDU, tmp);
	tmp = send (ncepu, __sent_frm, RBUF_SIZE, 0);
	ez_logger_notice (logger, "sent %d datas to " NCEPU, tmp);

	ez_logger_notice (logger, "processing event loop.");
	// while (1) loop
	ezevent_start_loop (loop);

	ez_logger_info (logger, "close sockets.");

	shutdown (baidu, SHUT_RDWR);
	shutdown (ncepu, SHUT_RDWR);
	close (baidu);
	close (ncepu);
	ez_logger_despose (&logger);
	return 0;
}


static void sock_readable 
(pezevent_loop _loop, int _fd, int _mask, void* _data) {
	int size = recv (_fd, _data, RBUF_SIZE, 0);
	if (size > 0) {
		char* ptr = _data;
		ptr [size] = '\0';
		ez_logger_notice (logger, 
				"fd %d received %d bytes datas.", _fd, size);
	} else 
		ez_logger_warn (logger, "receive error!");
}

static void sock_writable 
(pezevent_loop _loop, int _fd, int _mask, void* _data) {
	int size = send (_fd, _data, RBUF_SIZE, 0);
	if (size > 0) {
		char* ptr = _data;
		ptr [size] = '\0';
		ez_logger_notice (logger, 
				"fd %d sending %d bytes datas.", _fd, size);
	} else 
		ez_logger_warn (logger, "sending error!");
}


