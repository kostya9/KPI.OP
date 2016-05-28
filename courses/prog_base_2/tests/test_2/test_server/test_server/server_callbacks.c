#include "server_callbacks.h"
#include "request_dispatcher.h"
#include "request_handler.h"
#include "http_server.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http_server.h"
#include <curl\curl.h>
#include "student.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
int info_check(HTTP_METHOD method, char * path, char * content)
{
	if (method == HTTP_GET)
	{
		char buffer[PATH_LEN];
		strcpy(buffer, path);
		char * tok = strtok(buffer, "/");
		if (tok == NULL)
			return CHECK_NO;
		if (str_equal(tok, "info"))
		{
			return CHECK_YES;
		}
	}
	return CHECK_NO;
}

char * info_page(char * path, char * content, user_data * data)
{
	char * output = malloc(sizeof(char) * BUFFER_LENGTH);
	char * text = student_to_xml(&(data->student_info));
	sprintf(output, HTTP_VERSION " 200 OK\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(text), text);
	free(text);
	return output;
}

int external_check(HTTP_METHOD method, char * path, char * content)
{
	if (method == HTTP_GET)
	{
		char buffer[PATH_LEN];
		strcpy(buffer, path);
		char * tok = strtok(buffer, "/");
		if (tok == NULL)
			return CHECK_NO;
		if (str_equal(tok, "external"))
		{
			return CHECK_YES;
		}
	}
}
size_t writefunc(void * ptr, size_t size, size_t nmemb, char * out)
{
	strcat(out, ptr);
}
char * external_page(char * path, char * content, user_data * data)
{
	char * output = malloc(sizeof(char) * BUFFER_LENGTH);
	char buff[BUFFER_LENGTH] = "";
	CURL * curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://pb-homework.appspot.com/test/var/39?format=xml");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, buff);
	size_t res = curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);
	char * xmlDocString = strstr(buff, "\r\n\r\n");
	xmlDocPtr xmlDoc = xmlParseDoc(xmlDocString);
	xmlNodePtr node = xmlDoc->children;
	xmlNodePtr newNode = xmlNewNode(NULL, "time");

	xmlAddChild(node, )

	sprintf(output, HTTP_VERSION " 200 OK\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(buff), buff);
	return output;
}

void set_callback_info(request_dispatcher_t * dispatcher, student * student)
{
	dispatcher_add_request_function(dispatcher, info_check, info_page);
}
void set_callback_external(request_dispatcher_t * dispatcher)
{
	dispatcher_add_request_function(dispatcher, external_check, external_page);
}