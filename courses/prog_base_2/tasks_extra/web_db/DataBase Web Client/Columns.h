#pragma once
#include "MainHEaders.h"
#include <tuple>
enum COLUMN_TYPE { COLUMN_INT, COLUMN_STRING, COLUMN_ERROR };
typedef tuple<string, COLUMN_TYPE> column;
using namespace std;
class Columns {

private:
	vector<column> cols;
	column FindColByName(string name)
	{
		for (column c : cols)
			if (get<0>(c) == name)
				return c;
		throw out_of_range("NameNotAColumn");
	}
public:
	Columns(vector<column> cols)
	{
		this->cols = cols;
	}
	int GetColumnIndex(string name)
	{
		for (int i = 0; i < cols.size(); i++)
		{
			if (get<0>(cols.at(i)) == name)
				return i;
		}
		return -1;
	}
	COLUMN_TYPE GetColumnType(int index)
	{
		column c;
		try
		{
			c = cols.at(index);
		}
		catch (int e)
		{
			return COLUMN_ERROR;
		}
		COLUMN_TYPE tp = get<1>(c);
		return tp;
	}
	string GetColumnName(int index)
	{
		column c;
		try
		{
			c = cols.at(index);
		}
		catch (int e)
		{
			return "NULL";
		}
		string tp = get<0>(c);
		return tp;
	}
	int GetCount()
	{
		return cols.size();
	}
};