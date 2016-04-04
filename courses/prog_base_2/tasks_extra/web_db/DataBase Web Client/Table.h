#pragma once
#include "MainHeaders.h"
#include "Row.h"
#include "Columns.h"
#define MY_VARCHAR_LENGTH 45
// ONLY VARCHAR AND INTEGER
class Table
{
	private:
		string name;
		string column_primary_key;
		Columns * cols;
		vector <Row *> rows;
	public:
		// KEY ONLY INT BY NOW. HARDCODED THINGY
		Table(Columns * cols, vector <Row *> rows, string column_primary_key, string name)
		{
			this->name = name;
			this->cols = cols;
			this->rows = rows;
			this->column_primary_key = column_primary_key;
		}
		Table(Columns * cols, vector <Row *> rows, string column_primary_key)
		{
			this->name = string("Name is Not Set");
			this->cols = cols;
			this->rows = rows;
			this->column_primary_key = column_primary_key;
		}
		string GetKey()
		{
			return column_primary_key;
		}
		string GetName()
		{
			return name;
		}
		Columns * GetColumns()
		{
			return cols;
		}
		Row * GetRow(int index)
		{
			return rows.at(index);
		}
		int GetColumnsCount()
		{
			return cols->GetCount();
		}
		int GetRowsCount()
		{
			return rows.size();
		}
		~Table()
		{
			puts("Bye you table");
			for (Row * r : rows)
				delete r;
			delete cols;
		}

};