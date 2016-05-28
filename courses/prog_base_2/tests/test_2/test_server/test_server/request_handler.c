#include "request_handler.h"
#include "request_dispatcher.h"
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <malloc.h>
struct request_handler_s {
	handle_func response_generator;
	HTTP_METHOD method;
	char path[PATH_LEN];
	char content[CONTENT_LEN];
};

request_handler_t * handler_new(HTTP_METHOD method, char * path, char * content, handle_func func)
{
	request_handler_t * handler = (request_handler_t *)malloc(sizeof(request_handler_t));
	strcpy(handler->content, content);
	strcpy(handler->path, path);
	handler->method = method;
	handler->response_generator = func;
	return handler;
	
}

char * handler_get_response(char * output, request_handler_t * handler, void * data)
{
	char * response = handler->response_generator(handler->path, handler->content, data);
	strcpy(output, response);
	free(response);
	return output;
}

char * handler_get_path(char * output, request_handler_t * handler)
{
	strcpy(output, handler->path);
	return output;
}

char * handler_get_content(char * output, request_handler_t * handler)
{
	strcpy(output, handler->content);
	return output;
}

HTTP_METHOD handler_get_method(request_handler_t * handler)
{
	return handler->method;
}

request_handler_t * handler_delete(request_handler_t * self)
{
	free(self);
	return NULL;
}
