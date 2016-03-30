#pragma once
#include "MainHeaders.h"
namespace Table
{
	enum COLUMN_TYPE {COLUMN_INT, COLUMN_STRING};
	class Columns
	{
		struct column
		{
			string name;
			COLUMN_TYPE type;
		};
	private:
		vector <column> columns;
	public:
		string GetColumnName(int index)
		{
			return columns.at(index).name;
		}
		COLUMN_TYPE GetColumnType(int index)
		{
			return columns.at(index).type;
		}
		COLUMN_TYPE GetColumnType(string name)
		{
			for (column c : columns)
				if (name == c.name)
					return c.type;
		}
		int GetIndexByName(string name)
		{
			int i = 0;
			while (columns.at(i).name != name)
				i++;
			return i;
		}
	};
}