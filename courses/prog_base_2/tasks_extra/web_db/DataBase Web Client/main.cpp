// DataBase Web Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ServerHeaders.h"

int main()
{
	WSA wsa = WSA();
	Server server = Server("127.0.0.1", 80);
	server.Listen();
    return 0;	
}

