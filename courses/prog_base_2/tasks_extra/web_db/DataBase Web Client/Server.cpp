#include "Server.h"
#define CLRF "\r\n"

Server::Server(int port)
{
	this->server = Socket(port);
}

void Server::Listen()
{
	server.Bind();
	int listen = server.Listen();
	AcceptLoop();
}

string Server::MessageProccessing(string request)
{
	string response = "";
	response += "HTTP/1.1 200 OK" CLRF;
	response +=  ("Content-Type: text/html" CLRF);
	response += (CLRF);
	response += ("<p> Hello world </p>" CLRF);
	return response;
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
	}
	

}


Server::~Server()
{
}
