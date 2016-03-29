#pragma once
#include "MainHeaders.h"
#define URI_CAPACITY 100
#define CONTENT_CAPACITY 300
#define HTTP_VERSION "1.1"
enum REQUEST_TYPE {GET, SET, POST};
class HTTPRequest
{
	private:
		REQUEST_TYPE type;
		string uri;
		string content;
		size_t content_length;
	public:
		HTTPRequest(string request)
		{

		}

};