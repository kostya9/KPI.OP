#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket.h"

Socket::Socket(int port)
{
	SOCKET s;
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");// ANY IP <- Server NOPE
	this->sin = sin;
	if((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		s = NULL;
		fprintf(stderr, "Could not create socket : %d", WSAGetLastError());
		return;
	}
	this->s = s;
}

Socket::Socket(SOCKET server)
{
	SOCKADDR_IN client;
	int size = sizeof(struct sockaddr_in);
	SOCKET s = accept(server, (struct sockaddr *)&client, &size);
	this->s = s;
	this->sin = client;
	if (s == INVALID_SOCKET)
		this->s = NULL;
}

int Socket::Bind()
{
	int err = bind(s, (struct sockaddr *)&sin, sizeof(struct sockaddr_in));
	if(err == SOCKET_ERROR)
		fprintf(stderr, "Bind failed with error code : %d", WSAGetLastError());
	return err;
}

string Socket::Receive()
{
	char buffer[BUFFER_SIZE];
	int msg_size = recv(s, buffer, BUFFER_SIZE, NO_FLAGS_SET);
	if (msg_size < 0)
		return string("");
	buffer[msg_size] = '\0';
	return string(buffer);
}

int Socket::Send(string msg)
{
	int err = send(s, msg.c_str(), msg.length(), NO_FLAGS_SET);
	if (err < 0)
		puts("Send is fucked up");
	return err;
}

int Socket::Listen()
{
	return listen(s, 3);
}
