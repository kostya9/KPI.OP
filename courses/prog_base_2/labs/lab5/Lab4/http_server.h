#pragma once
#include "designers.h"
#include "response_manager.h"
typedef struct http_server_s http_server_t;

http_server_t * http_server_new();
void http_server_start(http_server_t * self, unsigned int port);
void http_server_delete(http_server_t * self);