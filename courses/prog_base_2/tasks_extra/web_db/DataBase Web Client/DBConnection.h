#pragma once
#include "Row.h"
#include "Columns.h"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#define MY_VARCHAR_LENGTH 45
using namespace sql;
using namespace std;
class DBConnection
{
	enum SQLTypeId { VARCHAR = -7, INTEGER = 4};
	private:
		Connection * con;
	public:
		DBConnection(string UID, string password)// Local thingy
		{
			Driver *driver;
			driver = get_driver_instance();
			con = driver->connect("tcp://127.0.0.1:3306", UID, password);
		}
		/*vector <Table::Row> GetRowsFromTable(string tableName)
		{
			vector <Table::Row> rows;
			Statement *stmt;
			ResultSet  *res;
			ResultSetMetaData * res_meta;
			res = stmt->executeQuery("SELECT * FROM webdata.mytable");
			res_meta = res->getMetaData();
			int column_count = res_meta->getColumnCount();
			for (int i = 0; i < column_count; i++)
			{
				SQLTypeId typeId = res_meta->getColumnType(i + 1);
				switch (typeId)
				{
					case VARCHAR:
					{
						char * column_name = res->getColumnName(i + 1);
						istream * name_Stream = res->getBlob(column_name);
						char pws[NAMELENGTH + 1]; // PASSWORD_LENGTH defined elsewhere; or use other functions to retrieve it
						name_Stream->getline(pws, NAMELENGTH);
						string name(pws);
						
					}break;
					case INTEGER:
					{

					} break;
					default:
						continue;
				}
			}
		}
		Table::Columns GetColumnsData(string tableName)
		{

		}*/
		void Close()
		{
			delete con;
			con = NULL;
		}
		//vector<Row> GetRowsFromTable(string TableName);
};