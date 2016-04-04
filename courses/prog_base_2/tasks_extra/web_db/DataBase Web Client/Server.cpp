#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"
#include "DBConnection.h"
#include "Table.h"
#include "HTMLBuilder.h"


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
string Server::GetParamValue(string path, string param_name)
{
	char * name_del = "?&=";
	const char * param_name_c_str = param_name.c_str();
	char buffer[BUFFER_SIZE];
	strcpy(buffer, path.c_str());
	char * pos = strtok(buffer, name_del); // BEFOR ?
	pos = strtok(NULL, name_del); // AFTER First
	while ( (pos = strtok(NULL, name_del)) != NULL)
	{
		char * name = strtok(NULL, name_del);
		if(strcmp(pos, param_name_c_str) == 0)
		{
			return string(name);
		}
	}
	return string("");
}

string Server::MessageProccessing(string request)
{
	HTTPRequest httprequest = HTTPRequest(request);
	int pos;
	if (httprequest.GetType() == GET)
	{
		string UID = string("web");
		string PWD = string("heyyoudon'tlookatthis");
		string path = httprequest.GetPath();
		string response_content;
		if (path.compare("/") == 0)
		{
			DBConnection * db = new DBConnection(UID, PWD);
			vector<string> table_names = db->GetTableNames(string(DATABASE_NAME));
			string content = HTMLBuilder::BuildTableNames(table_names);
			HTTPRequest response = HTTPRequest(HTTP_STATUS_OK, content);
			delete db;
			return response.ToString();
		}
		else if ((pos = path.find("?get")) != string::npos)
		{
			string tableName = GetParamValue(path, "table");
			//Connect to databse
			DBConnection * db = new DBConnection(UID, PWD);
			Table * table = db->GetTableFromDBTable(string(DATABASE_NAME) + "." + tableName);
			if (table == NULL)
				return string("INCORRECT TABLE");
			string content = HTMLBuilder::BuildHTMLTableFromDBTable(table);
			HTTPRequest response = HTTPRequest(HTTP_STATUS_OK, content);
			delete db;
			delete table;
			return response.ToString();

		}
		else if ((pos = path.find("?delete")) != string::npos)
		{
			DBConnection * db = new DBConnection(UID, PWD);
			string table_name = GetParamValue(path, "table");
			int key = stoi(GetParamValue(path, "key"));
			db->DeleteRow(table_name, key);
			//Connect to databse
			Table * table = db->GetTableFromDBTable(table_name);
			if (table == NULL)
				return string("INCORRECT TABLE");
			string content = HTMLBuilder::BuildHTMLTableFromDBTable(table);
			HTTPRequest response = HTTPRequest(HTTP_STATUS_OK, content);
			delete db;
			delete table;
			return response.ToString();
		}
		else if ((pos = path.find("?insert")) != string::npos)
		{
			DBConnection * db = new DBConnection(UID, PWD);
			string table_name = GetParamValue(path, "table");
			Table * table = db->GetTableFromDBTable(table_name);
			vector<string> vals_vec;
			vector <string> cols_vec;
			Columns *cols = table->GetColumns();
			int column_count = cols->GetCount();
			for (int i = 0; i < cols->GetCount(); i++)
			{
				string get_val = GetParamValue(path, cols->GetColumnName(i));
				string col = cols->GetColumnName(i);
				vals_vec.push_back(get_val);
				cols_vec.push_back(col);
			}
			db->InsertRow(table_name, cols_vec, vals_vec);
			int i = table_name.find(".");
			HTTPRequest response = HTTPRequest(HTTP_REDIRECT, string("Location"), string("\?get&table=") +	&table_name[i + 1]);
			delete db;
			delete table;
				return response.ToString();

		}
		else if ((pos = path.find("?form_new")) != string::npos)
		{
			DBConnection * db = new DBConnection(UID, PWD);
			string table_name = GetParamValue(path, "table");
			Table * table = db->GetTableFromDBTable(table_name);
			string content = HTMLBuilder::BuildFormNewEntry(table);
			HTTPRequest response = HTTPRequest(HTTP_STATUS_OK, content);
			delete db;
			delete table;
			return response.ToString();
		}
		else if ((pos = path.find("?edit")) != string::npos)
		{
			DBConnection * db = new DBConnection(UID, PWD);
			string table_name = GetParamValue(path, string("table"));
			string key = GetParamValue(path, string("key"));
			string key_column = db->GetPrimaryKey(table_name);
			Table * table = db->GetTableFromDBTable(table_name);
			vector<string> vals_vec;
			vector <string> cols_vec;
			Columns *cols = table->GetColumns();
			int column_count = cols->GetCount();
			for (int i = 0; i < cols->GetCount(); i++)
			{
				if (cols->GetColumnName(i) == table->GetKey())
					continue;
				string get_val = GetParamValue(path, cols->GetColumnName(i));
				string col = cols->GetColumnName(i);
				
				vals_vec.push_back(get_val);
				cols_vec.push_back(col);
			}
			db->UpdateRow(table_name, key, key_column, cols_vec, vals_vec);
			delete db;
			delete table;
			int i = table_name.find(".");
			HTTPRequest response = HTTPRequest(HTTP_REDIRECT, string("Location"), string("\?get&table=") + &table_name[i + 1]);
			return response.ToString();
			
		}
		else if ((pos = path.find("?form_edit")) != string::npos)
		{
			DBConnection * db = new DBConnection(UID, PWD);
			string table_name = GetParamValue(path, "table");
			Table * table = db->GetTableFromDBTable(table_name);
			string key = GetParamValue(path, string("key"));
			string content = HTMLBuilder::BuildFormEditEntry(table, table->GetKey(), key);
			HTTPRequest response = HTTPRequest(HTTP_STATUS_OK, content);
			delete db;
			delete table;
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
