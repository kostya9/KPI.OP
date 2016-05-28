#pragma once
#define HTTP_VERSION "HTTP/1.1"
#include "designer_db.h"
#include "student.h"
#define BUFFER_LENGTH 16384
#define XML_BUFFER_LENGTH 4096
typedef struct user_data {
	des_db_t * db;
	student student_info;
} user_data;

typedef struct http_server_s http_server_t;

http_server_t * http_server_new();
void http_server_start(http_server_t * self, unsigned int port);
void http_server_delete(http_server_t * self);