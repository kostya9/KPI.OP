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
		Table(Columns * cols, vector <Row *> rows, string column_primary_key, string name)
		{
			this->name = name;
			this->cols = cols;
			this->rows = rows;
		}
		Table(Columns * cols, vector <Row *> rows, string column_primary_key)
		{
			this->name = string("Name is Not Set");
			this->cols = cols;
			this->rows = rows;
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