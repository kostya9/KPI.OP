#pragma once
#include "libsocket\socket.h"
#include "request_dispatcher.h"
#include "http_server.h"
//#include "designers.h"
typedef struct http_server_s
{
	//designer * data;
	request_dispatcher_t * dispatcher;
	size_t size;
	size_t array_size;
	socket_t * socket;
	void * data;
} http_server_s;