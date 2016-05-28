#include <stdio.h>
#include <stdlib.h>
#include "http_server.h"
#include <winsock2.h>
int main(void)
{
	http_server_t * server = http_server_new();
	puts("Starting on port 8080...");
	http_server_start(server, 8080);
	int err = WSAGetLastError();
	printf("%i error occured", err);
	http_server_delete(server);
	return EXIT_SUCCESS;
}