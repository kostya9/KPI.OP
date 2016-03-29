#pragma once
#include<stdio.h>
#include<winsock2.h>
class WSA
{
	private:
		WSADATA wsa;
	public:
		WSA()
		{
			WSADATA wsa;
			if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			{
				fprintf(stderr, "Failed. Error Code : %d", WSAGetLastError());
				return;
			}
			this->wsa = wsa;
		}
		~WSA()
		{
			WSACleanup();
		}
};