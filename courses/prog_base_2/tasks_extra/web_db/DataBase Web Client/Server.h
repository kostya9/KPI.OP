#pragma once

#include "MainHeaders.h"
#include "Socket.h"
#include "HTTPRequest.h"
class Server
{
private:
	Socket server;
	string MessageProccessing(string request);
	void AcceptLoop();
public:
	Server(string ip, int port);
	void Listen();
	~Server();
};

