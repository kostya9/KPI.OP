#include "DBConnection.h"

void DBConnection::InsertRow(string table_name, vector<string> cols, vector<string> vals)
{
	Statement *stmt = con->createStatement();
	ResultSet  *res;
	ResultSetMetaData * res_meta;
	string query = "INSERT INTO " + table_name + "( ";
	for (int i = 0; i < cols.size(); i++)
	{
		if (i != 0)
			query += ",";
		query += cols.at(i);
	}
	query += ") VALUES (";
	for (int i = 0; i < vals.size(); i++)
	{
		if (i != 0)
			query += ",";
		query += "\"" + vals.at(i) + "\"";
	}
	query += ");";
	try
	{
		res = stmt->executeQuery(query);
	}
	catch (SQLException &e)
	{
		cout << " QUERY : " + query + "\n";
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* what() (derived from std::runtime_error) fetches error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return;
	}
}

// KEY ONLY INT BY NOW. HARDCODED THINGY

string DBConnection::GetPrimaryKey(string tableName)
{
	Statement *stmt = con->createStatement();
	ResultSet  *res;
	ResultSetMetaData * res_meta;
	string query = "SHOW INDEX FROM " + tableName;
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

void DBConnection::UpdateRow(string table_name, string key, string key_column, vector<string> cols, vector<string> vals)
{
	Statement *stmt = con->createStatement();
	ResultSet  *res;
	ResultSetMetaData * res_meta;
	string query = "UPDATE  " + table_name + " SET ";
	for (int i = 0; i < cols.size(); i++)
	{
		if (i != 0)
			query += ",";
		query += cols.at(i) + "=\"" + vals.at(i) + "\"";
	}
	query += " WHERE " + key_column + "=\"" + key + "\";";
	try
	{
		res = stmt->executeQuery(query);
	}
	catch (SQLException &e)
	{
		cout << " QUERY : " + query + "\n";
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* what() (derived from std::runtime_error) fetches error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return;
	}
}

void DBConnection::DeleteRow(string table, string key)
{
	string key_primary_name = this->GetPrimaryKey(table);
	Statement *stmt = con->createStatement();
	ResultSet  *res = NULL;
	string query = "DELETE FROM " + table +
		" WHERE " + key_primary_name + "='" + key + "'";
	try
	{
		res = stmt->executeQuery(query);
	}
	catch (SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* what() (derived from std::runtime_error) fetches error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	delete stmt;
	if (res != NULL)
		delete res;
}

void DBConnection::Close()
{
	delete con;
	con = NULL;
}
