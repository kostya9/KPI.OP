// DataBase Web Client.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4251)
#include "stdafx.h"
#include "ServerHeaders.h"
#include "Table.h"
#include <stdio.h>
#include <conio.h>
#include "Server.h"
using namespace std;
using namespace sql;
int main()
{
	WSA wsa = WSA();
	Server server = Server("127.0.0.1", 80);
	server.Listen();
	_getch();
	return 0;
}
