#pragma once
#include "MainHeaders.h"
#include <tuple>
#include "Columns.h"
class Row // ONLY STRINGS AND INTS
{
private:
	Columns * columns;
	vector <void *> values;
public:
	Row(Columns * columns, void * values[])
	{
		this->columns = columns;
		for (int i = 0; i < columns->GetCount(); i++)
			this->values.push_back(values[i]);
	}
	Columns GetColumns()
	{
		return *columns;
	}
	void * GetValue(int index)
	{
		return values.at(index);
	}
	~Row()
	{
		puts("Fuck you row");
		int i = 0;
		for (void * value : values)
		{
			switch (columns->GetColumnType(i))
			{
				case COLUMN_STRING:
				{
					delete (string *)value;
				}break;
				case COLUMN_INT:
				{
					delete (int *)value;
				}break;
			}
			i++;
		}
	}
};