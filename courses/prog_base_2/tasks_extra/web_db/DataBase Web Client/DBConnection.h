#pragma once
#include "Table.h"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
using namespace sql;
using namespace std;
class DBConnection
{
	enum SQLTypeId { VARCHAR = 13, INTEGER = 5};
	private:
		Connection * con;
	public:
		DBConnection(string UID, string password)// Local thingy
		{
			Driver *driver;
			driver = get_driver_instance();
			con = driver->connect("tcp://127.0.0.1:3306", UID.c_str(), password.c_str());
		}
		Table * GetTableFromDBTable(string tableName)
		{
			vector <Row *> rows_vec;
			vector <column> cols_vec;

			Statement *stmt = con->createStatement();
			ResultSet  *res;
			ResultSetMetaData * res_meta;
			res = stmt->executeQuery("SELECT * FROM webdata.mytable");
			res_meta = res->getMetaData();
			int column_count = res_meta->getColumnCount();
			// SETTING COLUMNS
			for (int i = 0; i < column_count; i++)
			{
				int typeId = res_meta->getColumnType(i + 1);
				switch (typeId)
				{
					case VARCHAR:
					{
						COLUMN_TYPE type = COLUMN_STRING;
						string column_name = res_meta->getColumnName(i + 1);
						column c = column(column_name, type);
						cols_vec.push_back(c);
					}break;
					case INTEGER:
					{
						COLUMN_TYPE type = COLUMN_INT;
						SQLString sql_Str = res_meta->getColumnName(i + 1);
						string column_name = sql_Str;
						column c = column(column_name, type);
						cols_vec.push_back(c);
					}break;
				}
			}
			Columns * cols = new Columns(cols_vec);
			// SETTING ROWS
			int columns_count = cols->GetCount();
			while (res->next())
			{
				vector <void *> values_vec;
				for (int i = 0; i < columns_count; i++)
				{

					COLUMN_TYPE type = cols->GetColumnType(i);
					switch (type)
					{
						case COLUMN_STRING:
						{
							string column_name = cols->GetColumnName(i);
							istream * str_Stream = res->getBlob(column_name.c_str());
							char arr[MY_VARCHAR_LENGTH + 1];// NAMELENGTH defined elsewhere (on top) - myVARCHAR size var -- HARDCODED ACTUALLY
							str_Stream->getline(arr, MY_VARCHAR_LENGTH);
							string * str_cur = new string(arr);
							values_vec.push_back(str_cur);
						}break;
						case COLUMN_INT:
						{
							string column_name = cols->GetColumnName(i);
							int value = res->getInt(column_name.c_str());
							int * int_cur = new int(value);
							values_vec.push_back(int_cur);
						} break;
						default:
							continue;
					}
				}
				Row * r = new Row(cols, (void **)&values_vec[0]);
				rows_vec.push_back(r);
			}
			return new Table(cols, rows_vec);
		}
		void Close()
		{
			delete con;
			con = NULL;
		}
		//vector<Row> GetRowsFromTable(string TableName);
};