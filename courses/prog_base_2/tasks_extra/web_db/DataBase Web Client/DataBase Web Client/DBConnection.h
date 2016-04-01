#pragma once
#include "MainHeaders.h"
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
	enum SQLTypeId { VARCHAR = 13, INTEGER = 5, CHAR = 11};
	private:
		Connection * con;
	public:
		DBConnection(string UID, string password)// Local thingy
		{
			Driver *driver;
			driver = get_driver_instance();
			con = driver->connect("tcp://127.0.0.1:3306", UID.c_str(), password.c_str());
		}
		string GetPrimaryKey(string tableName)
		{
			Statement *stmt = con->createStatement();
			ResultSet  *res;
			ResultSetMetaData * res_meta;
			string query = "SHOW INDEX FROM " + tableName ;
			res = stmt->executeQuery(query);
			res_meta = res->getMetaData();
			res->next();
			istream * str_Stream = res->getBlob("Column_name");
			char arr[MY_VARCHAR_LENGTH + 1];// NAMELENGTH defined elsewhere (on top) - myVARCHAR size var -- HARDCODED ACTUALLY
			str_Stream->getline(arr, MY_VARCHAR_LENGTH);
			string str_cur = string(arr);
			delete res;
			return str_cur;
		}
		Table * GetTableFromDBTable(string tableName)
		{
			vector <Row *> rows_vec;
			vector <column> cols_vec;

			Statement *stmt = con->createStatement();
			ResultSet  *res;
			ResultSetMetaData * res_meta;
			try
			{
				res = stmt->executeQuery("SELECT * FROM " + tableName);
			}
			catch (sql::SQLException &e)
			{
				return NULL;
			}
			string primary = GetPrimaryKey(tableName);
			res_meta = res->getMetaData();
			int column_count = res_meta->getColumnCount();
			// SETTING COLUMNS
			for (int i = 0; i < column_count; i++)
			{
				int typeId = res_meta->getColumnType(i + 1);
				switch (typeId)
				{
				case VARCHAR: case CHAR:
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
			return new Table(cols, rows_vec, primary, tableName);
		}
		vector<string> GetTableNames(string dbName)
		{
			vector <string> tables_vec;

			Statement *stmt = con->createStatement();
			ResultSet  *res;
			ResultSetMetaData * res_meta;
			string query = "SELECT TABLE_NAME "
				" FROM INFORMATION_SCHEMA.TABLES "
				" WHERE TABLE_TYPE = 'BASE TABLE' AND TABLE_SCHEMA = '" + dbName + "'";
			res = stmt->executeQuery(query);
			res_meta = res->getMetaData();
			while (res->next())
			{
				istream * str_Stream = res->getBlob(1);
				char arr[MY_VARCHAR_LENGTH + 1];// NAMELENGTH defined elsewhere (on top) - myVARCHAR size var -- HARDCODED ACTUALLY
				str_Stream->getline(arr, MY_VARCHAR_LENGTH);
				string str_cur = string(arr);
				tables_vec.push_back(str_cur);
			}
			return tables_vec;
		}
		
		void Close()
		{
			delete con;
			con = NULL;
		}
		//vector<Row> GetRowsFromTable(string TableName);
};