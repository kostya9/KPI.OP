#pragma once
#include <stdlib.h>
typedef struct http_server_s http_server_t;
void make_response(http_server_t * self, char * request, char * buffer, size_t buffer_size);