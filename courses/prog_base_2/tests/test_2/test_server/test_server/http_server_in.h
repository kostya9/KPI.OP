#pragma once
#define HTTP_VERSION "HTTP/1.1"
#define BUFFER_LENGTH 16384
#define XML_BUFFER_LENGTH 4096
#include "libsocket\socket.h"
#include "request_dispatcher.h"
#include "designer_db.h"
//#include "designers.h"
typedef struct user_data {
	des_db_t * db;
	char * student_info;
} user_data;
typedef struct http_server_s
{
	//designer * data;
	request_dispatcher_t * dispatcher;
	size_t size;
	size_t array_size;
	socket_t * socket;
	user_data data;
} http_server_s;