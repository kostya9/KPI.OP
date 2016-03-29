#include "Server.h"

Server::Server(string ip, int port)
{
	this->server = Socket(ip, port);
}

void Server::Listen()
{
	server.Bind();
	int listen = server.Listen();
	AcceptLoop();
}

string Server::MessageProccessing(string request)
{
	HTTPRequest httprequest = HTTPRequest(request);
	if (httprequest.GetType() == GET)
	{
		string path = httprequest.GetPath();
		string response_content;
		if (path.compare("/") == 0)
		{
			string content = ("<p> Hello world </p>");
			HTTPRequest response = HTTPRequest(HTTP_STATUS_OK, content);
			return response.ToString();
		}
		else // Page Not Found Proccessing
		{
			string content = ("<h1>Page not found!</h1>");
			HTTPRequest response = HTTPRequest(HTTP_STATUS_SERVER_ERROR, content);
			return response.ToString();
		}
	}
	else
		return string("ERROR");
}

void Server::AcceptLoop()
{
	while (1)
	{
		Socket client = Socket(server.GetSocket());
		char buffer[BUFFER_SIZE];
		string request = client.Receive();
		cout << "CONNECTED LOL :\n " + request + "\n";
		string response = MessageProccessing(request);
		client.Send(response);
		client.Close();
	}
	

}


Server::~Server()
{
}
