#include "http_server.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsocket\socket.h"
#include "http_server_in.h"
#include "request_dispatcher.h"
#include <curl\curl.h>
#include "server_callbacks.h"
#include "student.h"
char * page_not_found_handle(char * path, char * content, void *data)
{
	char * output = malloc(sizeof(char) * BUFFER_LENGTH);
	char * text = "Page was not found. Try again";
	sprintf(output, HTTP_VERSION " 404 PAGE NOT FOUND\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(text), text);
	return output;
}
char * home_page(char * path, char * content, void * data)
{
	char * output = malloc(sizeof(char) * BUFFER_LENGTH);
	char * text = "Hi here on the home page!";
	sprintf(output, HTTP_VERSION " 404 PAGE NOT FOUND\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(text), text);
	return output;
}
char * des_page(char * path, char * content, void * data)
{
	char * output = malloc(sizeof(char) * BUFFER_LENGTH);
	char buff[BUFFER_LENGTH] = "";
	//sprintf(output, HTTP_VERSION " 200 OK\n);
	int count = 0;
	des_db_t * db = ((user_data *)(data))->db;
	designer_t * designers = des_db_get_designers(db, &count);
	for (int i = 0; i < count; i++)
	{
		char tmp[100];
		sprintf(tmp, "ID : %i\n", designers[i].id);
		strcat(buff, tmp);
	}
	sprintf(output, HTTP_VERSION " 200 OK\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(buff), buff);
	return output;
}
int des_page_check(HTTP_METHOD method, char * path, char * content)
{
	if (method == HTTP_GET)
	{
		char buffer[BUFFER_LENGTH];
		strcpy(buffer, path);
		char * tok = strtok(buffer, "/");
		if (strcmp(tok, "designers") == 0)
		{
			return CHECK_YES;
		}
	}
	return CHECK_NO;
}
int home_page_check(HTTP_METHOD method, char * path, char * content)
{
	if (strcmp(path, "/") == 0)
		return CHECK_YES;
	return CHECK_NO;
}
http_server_t * http_server_new()
{
	lib_init();
	//int arr_size = 10;
	//designer * designers = malloc(arr_size * sizeof(designer));
	//int size = designers_fill_array(designers, arr_size);
	socket_t * socket = socket_new();
	http_server_t * server = malloc(sizeof(http_server_t));
	//server->size = size;
	request_dispatcher_t * dispatcher = dispatcher_new(page_not_found_handle);
	server->dispatcher = dispatcher;
	server->data = (user_data *)malloc(sizeof(user_data));
	((user_data *)(server->data))->db = des_db_new("des.db");
	((user_data *)(server->data))->student_info = student_new("Kostya Sharovarsky", "KP-52", 39);
	//server->array_size = arr_size;
	//server->data = designers;
	server->socket = socket;
	return server;
}

void http_server_start(http_server_t * self, unsigned int port)
{
	set_callback_info(self->dispatcher, &(((user_data *)(self->data))->student_info));
	set_callback_external(self->dispatcher);
	dispatcher_add_request_function(self->dispatcher, home_page_check, home_page);
	dispatcher_add_request_function(self->dispatcher, des_page_check, des_page);

	socket_bind(self->socket, port);
	socket_listen(self->socket);
	socket_t * client;
	char request_buffer[BUFFER_LENGTH];
	char response_buffer[BUFFER_LENGTH];
	while ((client = socket_accept(self->socket)) != NULL)
	{
		// Puts /0
		int sz = socket_read(client, request_buffer, BUFFER_LENGTH);
		request_handler_t * handler = dispatcher_get_handler(self->dispatcher, request_buffer);
		if (handler != NULL)
		{
			handler_get_response(response_buffer, handler, self->data); // TODO DATA
			handler_delete(handler);
		}
		else
		{
			sprintf(response_buffer, "");
		}
		socket_write(client, response_buffer, strlen(response_buffer));
		socket_close(client);
	}
}

void http_server_delete(http_server_t * self)
{
	socket_free(self->socket);
	free(self);
}
