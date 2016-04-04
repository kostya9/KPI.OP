#include "Table.h"

string Table::GetKey()
{
	return column_primary_key;
}

string Table::GetName()
{
	return name;
}

Columns * Table::GetColumns()
{
	return cols;
}

Row * Table::GetRow(int index)
{
	return rows.at(index);
}

int Table::GetColumnsCount()
{
	return cols->GetCount();
}

int Table::GetRowsCount()
{
	return rows.size();
}

Table::~Table()
{
	puts("Bye you table");
	for (Row * r : rows)
		delete r;
	delete cols;
}
