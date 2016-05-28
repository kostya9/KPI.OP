#pragma once
#include "request_handler.h"
#define DISPATCHER_REQUEST_BUFF_LEN 4096
#define PATH_LEN 256
#define CONTENT_LEN 4096
#define CHECK_YES 1
#define CHECK_NO 0
typedef int(*check_func)(HTTP_METHOD m, char *, char*);
typedef struct request_dispatcher_s request_dispatcher_t;

request_dispatcher_t * dispatcher_new(handle_func handle_not_found);
request_handler_t * dispatcher_get_handler(request_dispatcher_t * self, char * request);
void dispatcher_add_request_function(request_dispatcher_t * self, check_func check, handle_func func);
void dispatcher_add_not_found_function(request_dispatcher_t * self, handle_func func);