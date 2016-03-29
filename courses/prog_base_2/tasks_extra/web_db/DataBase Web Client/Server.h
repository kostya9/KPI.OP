#pragma once
#include "MainHeaders.h"
#include "Socket.h"
class Server
{
private:
	Socket server;
	string MessageProccessing(string request);
	void AcceptLoop();
public:
	Server(int port);
	void Listen();
	~Server();
};

