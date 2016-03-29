#pragma once
#include "MainHeaders.h"
#define URI_CAPACITY 100
#define CONTENT_CAPACITY 300
#define HTTP_VERSION "HTTP/1.1"
enum HTTP_STATUS {HTTP_STATUS_OK = 200, HTTP_STATUS_SERVER_ERROR = 500};
enum MESSAGE_TYPE {REQUEST, RESPONSE};
enum REQUEST_TYPE {GET, SET, POST, REQUEST_ERROR};
class HTTPRequest
{
	private:
		MESSAGE_TYPE msg_type;
		REQUEST_TYPE rqst_type;
		HTTP_STATUS HTTPstatus;
		string host;
		string path;
		size_t content_length;
		string content;
		REQUEST_TYPE GetRequestTypeFromRequest(string request);
		string GetPathFromRequest(string request);
		string HTTPStatusToString(HTTP_STATUS status);
	public:
		HTTPRequest(HTTP_STATUS HTTPstatus, string content)
		{
			this->msg_type = RESPONSE;
			this->HTTPstatus = HTTPstatus;
			this->content = content;
			this->content_length = content.length();
		}
		HTTPRequest(string request)
		{
			this->msg_type = REQUEST;
			rqst_type = GetRequestTypeFromRequest(request);
			path = GetPathFromRequest(request);
			content_length = 0;
		}
		REQUEST_TYPE GetType()
		{
			return rqst_type;
		}
		string GetPath()
		{
			return path;
		}
		string ToString();

};