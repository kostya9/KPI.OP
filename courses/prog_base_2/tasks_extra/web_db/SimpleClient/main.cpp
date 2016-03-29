//клиент
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include <iostream>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <winsock2.h>

//не забываем подключить ws2_32.lib
using namespace std;

int main()
{
	WSAData WSData;
	WSAStartup(0x101, &WSData);
	SOCKET S = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in SA;
	SA.sin_family = AF_INET;
	SA.sin_port = htons(80);
	SA.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int c = connect(S, (sockaddr*)&SA, sizeof(SA));
	printf("%i", c);
	if (send(S, "Hi", 2, 0) < 0)
		puts("Sending Failed");
	//string s;
	//cin >> s;
	char buf[1000];
	int rcv_size;
	while((rcv_size = recv(S, buf, 1000, 0)) == -1);
	buf[rcv_size] = '\0';
	cout << buf;
	//int n;
	//cin>>n;
	closesocket(S);
	cin >> buf;
	return 0;
}