#pragma once
typedef struct request_handler_s request_handler_t;
typedef char*(*handle_func)(char *, char *, void *data);
typedef enum HTTP_METHOD {HTTP_GET, HTTP_DELETE, HTTP_POST, HTTP_ERROR} HTTP_METHOD;


request_handler_t * handler_new(HTTP_METHOD method, char * path, char * content, handle_func func);
char * handler_get_response(char * output, request_handler_t * handler, void * data);
char * handler_get_path(char * output, request_handler_t * handler);
char * handler_get_content(char * output, request_handler_t * handler);
HTTP_METHOD handler_get_method(request_handler_t * handler);
request_handler_t * handler_delete(request_handler_t * self);