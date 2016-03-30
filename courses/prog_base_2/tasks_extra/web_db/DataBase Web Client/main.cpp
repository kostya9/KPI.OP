// DataBase Web Client.cpp : Defines the entry point for the console application.
//
#pragma warning(disable : 4251)
#include "stdafx.h"
#include "ServerHeaders.h"


#define NAMELENGTH 45
using namespace std;
using namespace sql;
int main()
{
	WSA wsa = WSA();
	Server server = Server("192.168.233.4", 80);
	server.Listen();
	return 0;
	/*Connection *con;
	Statement *stmt;
	ResultSet  *res;

	Driver *driver;
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "web", "heyyoudon'tlookatthis");
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT ID, Name FROM webdata.mytable ORDER BY id ASC");
	while (res->next()) {
		// You can use either numeric offsets...
		cout << "id = " << res->getInt(1);
		istream * name_Stream = res->getBlob("Name");
		char pws[NAMELENGTH + 1]; // PASSWORD_LENGTH defined elsewhere; or use other functions to retrieve it
		name_Stream->getline(pws, NAMELENGTH);
		string name(pws);
		cout << ", name = '" << name << "'" << endl;
	}
	delete res;
	delete stmt;
	delete con;*/
}
