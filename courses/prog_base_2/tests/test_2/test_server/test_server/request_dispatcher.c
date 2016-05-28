#include "request_dispatcher.h"
#include "request_handler.h"
#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "list\list.h"
#define str_equal(a, b) (strcmp(a, b) == 0)
typedef struct check_and_respond_s {
	check_func check;
	handle_func request;
} check_and_respond_t;
struct request_dispatcher_s
{
	list_t * check_and_respond_funcs;
	handle_func handle_not_found;
};
HTTP_METHOD  getMethod(char * name);
char * getPath(char * output, char * request);
char * getContent(char * buffer, char * request);

request_dispatcher_t * dispatcher_new(handle_func handle_not_found)
{
	request_dispatcher_t * self = malloc(sizeof(request_dispatcher_t));
	list_t * list = list_new();
	self->check_and_respond_funcs = list;
	self->handle_not_found = handle_not_found;
	return self;
}
request_handler_t * dispatcher_get_handler(request_dispatcher_t * self, char * request)
{
	char buffer[DISPATCHER_REQUEST_BUFF_LEN];
	char path[PATH_LEN];
	char content[CONTENT_LEN];
	
	strcpy(buffer, request);
	HTTP_METHOD method = getMethod(buffer);
	getPath(path, buffer);
	getContent(content, buffer);
	list_t * funcs = self->check_and_respond_funcs;
	size_t list_size = list_getSize(funcs);
	handle_func handle = NULL;
	for (unsigned int i = 0; i < list_size; i++)
	{
		check_and_respond_t * cur = list_get(funcs, i);
		check_func cur_check = cur->check;
		handle_func cur_handle = cur->request;
		if (cur_check(method, path, content))
		{
			handle = cur_handle;
			break;
		}
	}
	if (handle == NULL)
		handle = self->handle_not_found;
	return handler_new(method, path, content, handle);

}
void dispatcher_add_request_function(request_dispatcher_t * self, check_func check, handle_func func)
{
	list_t * list = self->check_and_respond_funcs;
	check_and_respond_t * ch_and_r = malloc(sizeof(check_and_respond_t));
	ch_and_r->check = check;
	ch_and_r->request = func;
	list_push_back(list, ch_and_r);
}
void dispatcher_add_not_found_function(request_dispatcher_t * self, handle_func func)
{
	self->handle_not_found = func;
}
char * getContent(char * output, char * request)
{
	char buffer[DISPATCHER_REQUEST_BUFF_LEN];
	strcpy(buffer, request);
	char * content = strstr(buffer, "\r\n\r\n");
	if (content == NULL)
	{
		sprintf(output, "");
		return output;
	}
	content += strlen("\r\n\r\n");
	strcpy(output, content);
	return output;
}
char * getPath(char * output, char * request)
{
	char buffer[DISPATCHER_REQUEST_BUFF_LEN];
	strcpy(buffer, request);

	char * tok = strtok(request, " ");
	tok = strtok(NULL, " ");
	strcpy(output, tok);
	return output;
}
HTTP_METHOD  getMethod(char * request)
{
	char buffer[DISPATCHER_REQUEST_BUFF_LEN];
	strcpy(buffer, request);
	char * name = strtok(buffer, " ");
	if (name == NULL)
		return HTTP_ERROR;
	if (str_equal(name, "GET"))
	{
		return HTTP_GET;
	}
	
	if (str_equal(name, "POST"))
	{
		return HTTP_POST;
	}

	if (str_equal(name, "DELETE"))
	{
		return HTTP_DELETE;
	}
	return HTTP_ERROR;
}