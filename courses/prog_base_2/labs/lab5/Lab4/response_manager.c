#include "response_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <float.h>
#include "http_server.h"
#include "http_server_in.h"
#include "html_builder.h"
typedef enum DESIGNER_CREATE_ERROR { ERROR_STRING_LENGTH, ERROR_NOT_ALL_PARAMETERS, ERROR_INCORRECT_DATE, ERROR_NO_ERROR, ERROR_NOT_NUMBER } DESIGNER_CREATE_ERROR;
static DESIGNER_CREATE_ERROR get_string_par(const char * content, char * name, char * buffer)
{
	if (content == NULL)
		return ERROR_NOT_ALL_PARAMETERS;
	char par_buffer[BUFFER_LENGTH];
	strcpy(par_buffer, content);
	char * name_tok = strstr(par_buffer, name);
	char * par = strtok(name_tok, "&=");
	par = strtok(NULL, "&=");
	if (par == NULL)
		return ERROR_STRING_LENGTH;
	if (strlen(par) > STRING_LENGTH_MAX)
		return ERROR_STRING_LENGTH;
	strcpy(buffer, par);
	return ERROR_NO_ERROR;
}
static HTTP_METHOD get_http_method(char * request)
{
	char buffer[BUFFER_LENGTH];
	strcpy(buffer, request);
	char * method_string = strtok(buffer, " ");
	if (method_string == NULL)
		return HTTP_UNKNOWN;
	if (strcmp(method_string, "GET") == 0)
		return HTTP_GET;
	if (strcmp(method_string, "POST") == 0)
		return HTTP_POST;
	if (strcmp(method_string, "DELETE") == 0)
		return HTTP_DELETE;
	if (strcmp(method_string, "OPTIONS") == 0)
		return HTTP_OPTIONS;
	return HTTP_UNKNOWN;
}
static void page_not_found(char * buffer, char * message)
{
	if (message == NULL)
		message = "Page not found. Sorry!";
	sprintf(buffer, HTTP_VERSION " 404 Not Found\n"
		"Content-length:%i\r\n\r\n"
		"%s", strlen(message), message);
}
static void response_ok(char * buffer, char * content)
{
	sprintf(buffer, HTTP_VERSION " 200 OK\n"
		"Content-length: %i\r\n\r\n"
		"%s", strlen(content), content);
}
static void make_response_get_api(http_server_t * self, char * address, char * buffer, size_t buffer_size)
{
	char address_buffer[BUFFER_LENGTH];

	strcpy(address_buffer, address);
	char * items = strtok(address_buffer, "/?");
	if (items == NULL)
	{
		page_not_found(buffer, NULL);
		return;
	}
	if (strcmp(items, "designers") == 0)
	{
		strcpy(address_buffer, address);
		char * des_id = strtok(address_buffer, "/");
		des_id = strtok(NULL, "/");
		designer_t * des_filtered = NULL;
		size_t size = 0;
		if (des_id == NULL)
		{
			strcpy(address_buffer, address);
			char * tok = strtok(address_buffer, "?");
			tok = strtok(NULL, "?");
			if(tok != NULL)
			{
				char tok_buf[BUFFER_LENGTH];
				DESIGNER_CREATE_ERROR rc = get_string_par(tok, "projectCount_gt", tok_buf);
				int projectCount_gt = -1;
				if(rc == ERROR_NO_ERROR)
					projectCount_gt = atoi(tok_buf);
				rc = get_string_par(tok, "salary_ls", tok_buf);
				float salary_ls = FLT_MAX;
				if (rc == ERROR_NO_ERROR)
					salary_ls = atoi(tok_buf);
				des_filtered = des_db_get_filtered_designers(self->con, projectCount_gt, salary_ls, &size);
			}
			else
			{
				des_filtered = self->data;
				size = self->size;
			}
			char designers_xml_buffer[XML_BUFFER_LENGTH];
			designer_array_to_xml_string(designers_xml_buffer, XML_BUFFER_LENGTH, des_filtered, size);
			response_ok(buffer, designers_xml_buffer);
		}
		else
		{
			char designer_xml_buffer[XML_BUFFER_LENGTH];
			int id = atoi(des_id);
			designer_t * des = des_db_get_designer(self->con, id);
			if (des != NULL)
			{
				designer_to_xml_string(designer_xml_buffer, XML_BUFFER_LENGTH, des);
				response_ok(buffer, designer_xml_buffer);
			}
			else
			{
				page_not_found(buffer, "Designer with this id was not found");
			}
		}
		return;
	}
	else
	{
		page_not_found(buffer, NULL);
		return;
	}
}
void make_response_get_designers(http_server_t * self, char * address, char * buffer, size_t buffer_size)
{
	char address_buffer[BUFFER_LENGTH];
	strcpy(address_buffer, address);
 	char * first = strtok(address_buffer, "/");
	if (first == NULL)
	{
		char des_buffer[BUFFER_LENGTH];
		html_builder_designers(self, des_buffer);
		response_ok(buffer, des_buffer);
	}
	else
	{
		int id = atoi(first);
		designer_t * des = des_db_get_designer(self->con, id);
		if (des == NULL)
		{
			page_not_found(buffer, "There is no such designers");
		}
		else
		{
			char designer_buffer[BUFFER_LENGTH];
			html_builder_designer(self, des, designer_buffer);
			response_ok(buffer, designer_buffer);
		}
	}
}
static void make_response_get(http_server_t * self, char * address, char * buffer, size_t buffer_size)
{
	char address_buffer[BUFFER_LENGTH];
	strcpy(address_buffer, address);
	char * first = strtok(address_buffer, "/");
	if (first == NULL)
	{
		char home_buffer[BUFFER_LENGTH];
		html_builder_home(self, home_buffer);
		response_ok(buffer, home_buffer);
		return;
	}
	if (strcmp(first, "api") == 0)
	{
		strcpy(address_buffer, address + (address_buffer - first) + 5);
		make_response_get_api(self, address_buffer, buffer, buffer_size);
	}
	else if (strcmp(first, "designers") == 0)
	{
		strcpy(address_buffer, address + (address_buffer - first) + strlen("designers") + 2);
		make_response_get_designers(self, address_buffer, buffer, buffer_size);
	}
	else if (strcmp(first, "new-designer") == 0)
	{
		char html_buf[BUFFER_LENGTH];
		html_builder_new_designer(self, html_buf);
		response_ok(buffer, html_buf);
	}
	else
		page_not_found(buffer, "PAGE NOT FOUND");
}
static void make_response_delete_api(http_server_t * self, char * address, char * buffer, size_t buffer_size)
{
	char address_buffer[BUFFER_LENGTH];
	strcpy(address_buffer, address);
	char * items = strtok(address_buffer, "/");
	if (items == NULL)
	{
		page_not_found(buffer, NULL);
		return;
	}
	if (strcmp(items, "designers") == 0)
	{
		char * des_id = strtok(NULL, "/");
		if (des_id != NULL)
		{
			int id = atoi(des_id);
			des_db_delete_designer(self->con, id);
			int prevSize = self->size;
			self->data = des_db_get_designers(self->con, &(self->size));
			if (self->size == prevSize - 1)
			{
				response_ok(buffer, "Deletion successfull");
			}
			else
			{
				page_not_found(buffer, "Designer with this id was not found");
			}
		}
		else
		{
			page_not_found(buffer, "Choose id for DELETE");
			return;
		}
	}
	else
	{
		page_not_found(buffer, "Not appripriate address for DELETE");
		return;
	}
}
static void make_response_delete(http_server_t * self, char * address, char * buffer, size_t buffer_size)
{
	char address_buffer[BUFFER_LENGTH];
	strcpy(address_buffer, address);
	char * first = strtok(address_buffer, "/");
	if (first == NULL)
	{
		page_not_found(buffer, "Not appripriate address for DELETE");
		return;
	}
	if (strcmp(first, "api") == 0)
	{
		strcpy(address_buffer, address + (address_buffer - first) + 5);
		make_response_delete_api(self, address_buffer, buffer, buffer_size);
	}
	else if ((strcmp(first, "designers")) == 0)
	{
		char * id_c = strtok(NULL, "/");
		int id = atoi(id_c);
		des_db_delete_designer(self->con, id);
		self->data = des_db_get_designers(self->con, &(self->size));
	}
}
static int is_number(char * buffer)
{
	int size = strlen(buffer);
	for (int i = 0; i < size; i++)
	{
		if (isdigit(buffer[i]) == 0)
			return 0;
	}
	return 1;
}
static int is_float(char * buffer)
{
	int dot = 0;
	int size = strlen(buffer);
	for (int i = 0; i < size; i++)
	{
		if (isdigit(buffer[i]) == 0)
		{
			if (buffer[i] == '.')
				dot++;
			else
				return 0;
		}
	}
	if (dot > 1)
		return 0;
	return 1;
}
static time_t make_date(char * buffer)
{
	int day, month, year;
	int status = sscanf(buffer, "%i-%i-%i", &year, &month, &day);
	if (status != 3)
		return 0;
	struct tm date;
	memset(&date, 0, sizeof(struct tm));
	if (day > 31 || day < 1 || month > 12 || month < 1 || year < 0 || year > 2016)
		return 0;
	date.tm_mday = day;
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	time_t t;
	t = mktime(&date);
	return t;

}
static DESIGNER_CREATE_ERROR create_designer(http_server_t * self, char  * content, designer_t ** designer_cr)
{
	char name_buf[BUFFER_LENGTH];
	DESIGNER_CREATE_ERROR rc = get_string_par(content, "name", name_buf);
	if (rc != ERROR_NO_ERROR)
		return rc;

	char surname_buf[BUFFER_LENGTH];
	rc = get_string_par(content, "surname", surname_buf);
	if (rc != ERROR_NO_ERROR)
		return rc;

	char experienceyears_buf[BUFFER_LENGTH];
	rc = get_string_par(content, "experienceyears", experienceyears_buf);
	if (rc != ERROR_NO_ERROR)
		return rc;
	if (is_number(experienceyears_buf) == 0)
		return ERROR_NOT_NUMBER;
	int excperienceYears = atoi(experienceyears_buf);

	char averageVertices_buf[BUFFER_LENGTH];
	rc = get_string_par(content, "averageVertices", averageVertices_buf);
	if (rc != ERROR_NO_ERROR)
		return rc;
	if (is_float(averageVertices_buf) == 0)
		return ERROR_NOT_NUMBER;
	float averageVertices = atof(averageVertices_buf);

	char hireDate_buf[BUFFER_LENGTH];
	rc = get_string_par(content, "hireDate", hireDate_buf);
	if (rc != ERROR_NO_ERROR)
		return rc;
	time_t hireDate = make_date(hireDate_buf);
	designer_t * new_des = &((self->data)[self->size]);
	strcpy(new_des->name, name_buf);
	strcpy(new_des->surname, surname_buf);
	new_des->experience = excperienceYears;
	new_des->averageVertices = averageVertices;
	new_des->hireDate = hireDate;
	des_db_add_designer(self->con, new_des);
	*designer_cr = new_des;
	return ERROR_NO_ERROR;

}
//name=&surname=&experienceyears=&averageVertices=&hireDate=
static void make_response_post_api(http_server_t * self, char * address, char * content, char * buffer, size_t buffer_size)
{
	char address_buffer[BUFFER_LENGTH];
	strcpy(address_buffer, address);
	char * items = strtok(address_buffer, "/");
	if (items == NULL)
	{
		page_not_found(buffer, NULL);
		return;
	}
	if (strcmp(items, "designers") == 0)
	{
		char * next = strtok(NULL, "/");
		if (next == NULL)
		{
			designer_t * des_cr;
			DESIGNER_CREATE_ERROR rc = create_designer(self, content, &des_cr);
			self->data = des_db_get_designers(self->con, &(self->size));
			switch (rc)
			{
				case ERROR_NO_ERROR:
				{
					char xml_buffer[XML_BUFFER_LENGTH];
					designer_to_xml_string(xml_buffer, XML_BUFFER_LENGTH, des_cr);
					response_ok(buffer, xml_buffer);
				}break;
				default:
					page_not_found(buffer, "ERROR COULD NOT CREATE DESIGNER");
			}
		}
		else
		{
			page_not_found(buffer, "Not appripriate address for POST");
			return;
		}
	}
	else
	{
		page_not_found(buffer, "Not appripriate address for POST");
		return;
	}
}
static void make_response_post(http_server_t * self, char * address, char * content, char * buffer, size_t buffer_size)
{
	char address_buffer[BUFFER_LENGTH];
	strcpy(address_buffer, address);
	char * first = strtok(address_buffer, "/");
	if (first == NULL)
	{
		page_not_found(buffer, "Not appripriate address for POST");
		return;
	}
	if (strcmp(first, "api") == 0)
	{
		strcpy(address_buffer, address + (address_buffer - first) + 5);
		make_response_post_api(self, address_buffer, content, buffer, buffer_size);
	}
	else if (strcmp(first, "designers") == 0)
	{
		designer_t * des_cr;
		DESIGNER_CREATE_ERROR rc = create_designer(self, content, &des_cr);
		self->data = des_db_get_designers(self->con, &(self->size));
		switch (rc)
		{
		case ERROR_NO_ERROR:
		{
			char xml_buffer[XML_BUFFER_LENGTH];
			designer_to_xml_string(xml_buffer, XML_BUFFER_LENGTH, des_cr);
			sprintf(buffer, HTTP_VERSION " 301 REDIRECT\nLocation : \designers\r\n\r\n");
		}break;
		default:
			page_not_found(buffer, "ERROR COULD NOT CREATE DESIGNER");
		}
	}
	else
	{
		page_not_found(buffer, "Not appripriate address for POST");
		return;
	}
}
void make_response(http_server_t * self, char * request, char * buffer, size_t buffer_size)
{
	char req_buffer[BUFFER_LENGTH];
	strcpy(req_buffer, request);
	HTTP_METHOD method = get_http_method(request);
	if (method == HTTP_GET)
	{
		char * address = strtok(req_buffer, " ");
		address = strtok(NULL, " ");
		make_response_get(self, address, buffer, buffer_size);
	}
	else if (method == HTTP_DELETE)
	{
		char * address = strtok(req_buffer, " ");
		address = strtok(NULL, " ");
		make_response_delete(self, address, buffer, BUFFER_LENGTH);
	}
	else if (method == HTTP_POST)
	{
		char buffer_addr[BUFFER_LENGTH];
		strcpy(buffer_addr, req_buffer);
		char buffer_cont[BUFFER_LENGTH];
		strcpy(buffer_cont, req_buffer);
		char * address = strtok(buffer_addr, " ");
		address = strtok(NULL, " ");
		char * content = strstr(buffer_cont, "\r\n\r\n");
		content = strtok(content, "\r\n\r\n");
		make_response_post(self, address, content, buffer, buffer_size);
	}
	else if(method == HTTP_OPTIONS)
	{
		sprintf(buffer,
			"HTTP/1.1 200 OK\n"
			"Access-Control-Allow-Origin: *\n"
			"Access-Control-Allow-Methods: DELETE\n"
			"\n");
	}
}
