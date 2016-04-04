#include "HTTPRequest.h"

REQUEST_TYPE HTTPRequest::GetRequestTypeFromRequest(string request)
{
	if (request.find("GET") == 0)
		return GET;
	else if (request.find("SET") == 0)
		return SET;
	else if (request.find("POST") == 0)
		return POST;
	else 
		return REQUEST_ERROR;
}

string HTTPRequest::GetPathFromRequest(string request)
{
	char *next_token = NULL; // WTF is this?
	char * delimeters = " ";
	char * curPos;
	char buffer[BUFFER_SIZE];
	strcpy_s(buffer, sizeof(char) * BUFFER_SIZE, request.c_str());
	curPos = strtok_s(buffer, delimeters, &next_token);
	curPos = strtok_s(NULL, delimeters, &next_token);
	if (curPos == NULL)
		return "";
	return string(curPos);
}

string HTTPRequest::HTTPStatusToString(HTTP_STATUS status)
{
	switch (status)
	{
		case HTTP_STATUS_OK:
			return "OK";
		default:
			return "SERVER_ERROR";
	}
}

string HTTPRequest::ToString()
{
	switch (msg_type)
	{
		case REQUEST:
		{
			// No Need Now
			return "";
		}break;
		case RESPONSE:
		{
			string response = "";
			response += HTTP_VERSION + string(" ") + to_string(HTTPstatus) + " " + HTTPStatusToString(HTTPstatus) + CRLF;
			if(header.length() != 0)
				response += header + ":" + header_content;
			if (content_length == 0)
				return response;
			response += "Content-length: " + to_string(content_length) + CRLF + CRLF + content;
			return response;
		}break;
	}
}
