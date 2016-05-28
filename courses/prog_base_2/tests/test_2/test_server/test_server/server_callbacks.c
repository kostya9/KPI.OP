#include "server_callbacks.h"
#include "request_dispatcher.h"
#include "request_handler.h"
#include "http_server.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http_server.h"
#include <curl\curl.h>
#include <time.h>
#include "student.h"
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
#include <libxml/tree.h>
#include "FSHelper\FSHELPER.h"
#include <Windows.h>
#define WINDOWS_TICK 10000000
#define SEC_TO_UNIX_EPOCH 11644473600LL

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
		"Content-type:text\\xml\n"
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
	return CHECK_NO;
}

int database_check(HTTP_METHOD method, char * path, char * content)
{
	if (method == HTTP_GET)
	{
		char buffer[PATH_LEN];
		strcpy(buffer, path);
		char * tok = strtok(buffer, "/");
		if (tok == NULL)
			return CHECK_NO;
		if (str_equal(tok, "database"))
		{
			return CHECK_YES;
		}
	}
	return CHECK_NO;
}
static void designer_to_xml_buffer(xmlTextWriterPtr writer, designer_t * designer)
{
	int bytes_written;
	char write_buffer[100];
	bytes_written = xmlTextWriterStartElement(writer, (xmlChar*)"designer");
	sprintf(write_buffer, "%i", designer->id);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"id", (xmlChar*)write_buffer);
	//Name
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"name", (xmlChar*)designer->name);
	//Surname
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"surname", (xmlChar*)designer->surname);
	// Statistics
	bytes_written = xmlTextWriterStartElement(writer, (xmlChar*)"statistics");

	//Double to string
	sprintf(write_buffer, "%.2f", designer->averageVertices);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"averageVertices", (xmlChar*)write_buffer);
	// Time to standart time
	struct tm *tminfo;
	tminfo = localtime(&(designer->hireDate));
	sprintf(write_buffer, "%i-%i-%i", tminfo->tm_year + 1900, tminfo->tm_mon + 1, tminfo->tm_mday);
	bytes_written = xmlTextWriterWriteElement(writer, (xmlChar*)"hireDate", (xmlChar*)write_buffer);
	bytes_written = xmlTextWriterEndElement(writer);

	bytes_written = xmlTextWriterEndElement(writer);
}
char * database_page(char * path, char * content, user_data * data)
{
	size_t size = 0;
	char * output = malloc(sizeof(char) * BUFFER_LENGTH);
	char buffer[BUFFER_LENGTH] = "";
	xmlTextWriterPtr writer;
	xmlBufferPtr xml_buf;
	xml_buf = xmlBufferCreate();
	writer = xmlNewTextWriterMemory(xml_buf, 0);
	xmlTextWriterStartDocument(writer, "1.0", "ASCII", NULL);
	xmlTextWriterStartElement(writer, "designers");
	designer_t * des = des_db_get_designers(data->db, &size);
	for (int i = 0; i < size; i++)
	{
		designer_to_xml_buffer(writer, &(des[i]));
	}
	xmlTextWriterEndElement(writer);
	xmlTextWriterEndDocument(writer);
	xmlFreeTextWriter(writer);
	strcpy(buffer, xml_buf->content);
	sprintf(output, HTTP_VERSION " 200 OK\n"
		"Content-type:text\\xml\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(buffer), buffer);
	return output;
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
	char * xmlDocString = buff;
	xmlDocPtr xmlDoc = xmlParseDoc(xmlDocString);
	xmlNodePtr node = xmlDoc->children;
	xmlNodePtr newNode = xmlNewNode(NULL, "time");
	time_t cur_time = time(NULL);
	struct tm * tm_cur = localtime(&cur_time);
	char timeBuff[100];
	sprintf(timeBuff, "%d-%d-%d", tm_cur->tm_year + 1900, tm_cur->tm_mon + 1, tm_cur->tm_mday);
	xmlNodeAddContent(newNode, timeBuff);
	xmlAddChild(node, newNode);
	char * buffer;
	int size = 0;
	xmlDocDumpMemory(xmlDoc, &buffer, &size);
	sprintf(output, HTTP_VERSION " 200 OK\n"
		"Content-type:text\\xml\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(buffer), buffer);
	xmlFree(buffer);
	return output;
}
int dir_check(HTTP_METHOD method, char * path, char * content)
{
	if (method == HTTP_GET)
	{
		char buffer[PATH_LEN];
		strcpy(buffer, path);
		char * tok = strtok(buffer, "/");
		if (tok == NULL)
			return CHECK_NO;
		if (str_equal(tok, "dir"))
		{
			return CHECK_YES;
		}
	}
	return CHECK_NO;
}

unsigned WindowsTickToUnixSeconds(long long windowsTicks)
{
	return (unsigned)(windowsTicks / WINDOWS_TICK - SEC_TO_UNIX_EPOCH);
}
char * dir_page(char * path, char * content, user_data * data)
{
	char * output = malloc(sizeof(char) * BUFFER_LENGTH);
	char buffer[PATH_LEN];
	TCHAR buff[PATH_LEN];
	strcpy(buffer, path);
	char fileSystemPath[BUFFER_LENGTH];
	GetCurrentDirectoryA(BUFFER_LENGTH, fileSystemPath);
	//GetModuleFileNameA(NULL, fileSystemPath, BUFFER_LENGTH);

	char * dir_name = strtok(buffer, "/");
	dir_name = strtok(NULL, "/");
	
	int is_dir_existing = 1;
	if(dir_name != NULL)
		is_dir_existing = dir_exists(dir_name);
	else
	{
		dir_name = "\\";
	}
	strcat(fileSystemPath, dir_name);
	if (is_dir_existing == 0)
	{
		char * text = "Page was not found. Try again";
		sprintf(output, HTTP_VERSION " 404 PAGE NOT FOUND\n"
			"Content-length : %d"
			"\r\n\r\n%s", strlen(text), text);
		return output;
	}

	list_t * files = dir_getFilesList(fileSystemPath);
	int count = list_getSize(files);
	char csv_buf[BUFFER_LENGTH] = "";
	for (int i = 0; i < count; i++)
	{
		char csv_buf_temp[1000];
		char * fileName = list_get(files, i);
		wchar_t text_w[100];
		mbstowcs(text_w, fileName, strlen(fileName) + 1);//Plus null
		LPWSTR ptr = text_w;
		HANDLE f = CreateFile(ptr, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
		if (f == INVALID_HANDLE_VALUE)
			continue;
		int i = GetLastError();
		FILETIME ftime;
		GetFileTime(
			f,
			&ftime,
			NULL,
			NULL
			);
		CloseHandle(f);
		/*ULARGE_INTEGER ull;
		ull.LowPart = ftime.dwLowDateTime;
		ull.HighPart = ftime.dwHighDateTime;*/
		SYSTEMTIME time_sys;
		FileTimeToSystemTime(&(ftime), &time_sys);
		sprintf(csv_buf_temp, "\"%s\", \"%i-%i-%i\",\n", fileName, time_sys.wYear, time_sys.wMonth, time_sys.wDay);
		strcat(csv_buf, csv_buf_temp);
	}
	csv_buf[strlen(csv_buf) - 2] = '\0';
	sprintf(output, HTTP_VERSION " 200 OK\n"
		"Content-type:text\\csv\n"
		"Content-length : %d"
		"\r\n\r\n%s", strlen(csv_buf), csv_buf);
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

void set_callback_database(request_dispatcher_t * dispatcher)
{
	dispatcher_add_request_function(dispatcher, database_check, database_page);
}
void set_callback_dir(request_dispatcher_t * dispatcher)
{
	dispatcher_add_request_function(dispatcher, dir_check, dir_page);
}