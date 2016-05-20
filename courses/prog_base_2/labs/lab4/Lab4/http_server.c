#include "http_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsocket\socket.h"
#include "designers.h"
#include "http_server_in.h"
#include "http_server_in.h"
http_server_t * http_server_new()
{
	int arr_size = 10;
	designer * designers = malloc(arr_size * sizeof(designer));
	int size = designers_fill_array(designers, arr_size);
	socket_t * socket = socket_new();
	http_server_t * server = malloc(sizeof(http_server_s));
	server->size = size;
	server->array_size = arr_size;
	server->data = designers;
	server->socket = socket;
	return server;
}

void http_server_start(http_server_t * self, unsigned int port)
{

	socket_bind(self->socket, port);
	socket_listen(self->socket);
	socket_t * client;
	char request_buffer[BUFFER_LENGTH];
	char response_buffer[BUFFER_LENGTH];
	while ((client = socket_accept(self->socket)) != NULL)
	{
		// Puts /0
		int sz = socket_read(client, request_buffer, BUFFER_LENGTH);
		make_response(self, request_buffer, response_buffer, BUFFER_LENGTH);	
		socket_write(client, response_buffer, strlen(response_buffer));
		socket_close(client);
	}
}

void http_server_delete(http_server_t * self)
{
	socket_free(self->socket);
	free(self);
}
