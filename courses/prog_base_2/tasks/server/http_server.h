#pragma once
typedef struct http_server_s http_server_t;

http_server_t * http_server_new(int port);
void http_server_start(http_server_t * server, char * path_to_designers);
void http_server_delete(http_server_t * server);
