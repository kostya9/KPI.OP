#pragma once
#define HTTP_VERSION "HTTP/1.1"
#define BUFFER_LENGTH 16384
#define XML_BUFFER_LENGTH 4096
#include "libsocket\socket.h"
#include "designers.h"
typedef enum HTTP_METHOD { HTTP_GET, HTTP_POST, HTTP_DELETE, HTTP_OPTIONS, HTTP_UNKNOWN } HTTP_METHOD;
typedef struct http_server_s
{
	designer * data;
	size_t size;
	size_t array_size;
	socket_t * socket;
} http_server_s;