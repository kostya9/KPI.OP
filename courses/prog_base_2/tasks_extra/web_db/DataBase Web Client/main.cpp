// DataBase Web Client.cpp : Defines the entry point for the console application.
//
#pragma warning(disable : 4251)
#include "stdafx.h"
#include "ServerHeaders.h"
#include "Table.h"
#include <stdio.h>
#include <conio.h>
#define NAMELENGTH 45
using namespace std;
using namespace sql;
int main()
{
	/*WSA wsa = WSA();
	Server server = Server("192.168.233.4", 80);
	server.Listen();
	return 0;*/
	string UID = string("web");
	string PWD = string("heyyoudon'tlookatthis");
	DBConnection * db = new DBConnection(UID, PWD);
	Table * table = db->GetTableFromDBTable("webdata.myTable");
	Columns * cols = table->GetColumns();
	int columns_count = table->GetColumnsCount();
	int rows_count = table->GetRowsCount();
	for (int i = 0; i < rows_count; i++)
	{
		Row * row = table->GetRow(i);
		for (int k = 0; k < columns_count; k++)
		{
			puts(cols->GetColumnName(k).c_str());
			COLUMN_TYPE type = cols->GetColumnType(k);
			switch (type)
			{
				case COLUMN_STRING:
				{
					string * cur_str_p = (string *)row->GetValue(k); // Strange Behaviour here. Something like memory deallocation. YEP IT WAS TRUE. But fixed
					string cur_str = *cur_str_p;
					printf("%20s", cur_str.c_str());
				}break;
				case COLUMN_INT:
				{
					int * cur_int_p = (int *)row->GetValue(k);
					int cur_int = *cur_int_p;
					printf("%3i", cur_int);
				}break;
			}
			puts("");
		}
		puts("");
	}

	delete table;
	delete db;
	_getch();
}
