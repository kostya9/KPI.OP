#pragma once
#include "MainHeaders.h"
#include "Row.h"
#include "Columns.h"
#define MY_VARCHAR_LENGTH 45
// ONLY VARCHAR AND INTEGER
class Table
{
	private:
		Columns * cols;
		vector <Row *> rows;
	public:
		Table(Columns * cols, vector <Row *> rows)
		{
			this->cols = cols;
			this->rows = rows;
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
			puts("Fuck you table");
			for (Row * r : rows)
				delete r;
			delete cols;
		}

};