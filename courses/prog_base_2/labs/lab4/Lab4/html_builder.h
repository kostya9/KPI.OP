#pragma once
#include "http_server_in.h"
#include "designers.h"
typedef struct http_server_s http_server_t;
void html_builder_home(http_server_t * self, char * buffer);
void html_builder_designers(http_server_t * self, char * buffer);
void html_builder_designer(http_server_t * self, designer * des, char * buffer);
void html_builder_new_designer(http_server_t * self, char * buffer);