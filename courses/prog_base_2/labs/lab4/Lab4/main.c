#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "libsocket\socket.h"
#include "http_server.h"
int main(void)
{
	lib_init();
	http_server_t * server = http_server_new();
	http_server_start(server, 8080);
	http_server_delete(server);
	lib_free();
	return EXIT_SUCCESS;
}