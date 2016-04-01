#pragma once
class HTMLBuilder
{
	public:
		// With Links
		static string BuildTableNames(vector<string> names)
		{
			int names_count = names.size();
			string html_table = "";
			html_table += "<table border=1>";
			html_table += string("<caption> ") + "TABLES in database" + " </caption>";
			// SET COLUMN NAMES
			html_table += "<tr>";
			for (int i = 0; i < names_count; i++)
			{
				string table_name = names.at(i);
				html_table += "<th>";
				html_table += "<a href=\"\\?table=" + table_name + "\">";
				html_table += table_name;
				html_table += "</a>";
				html_table += "</th>";
			}
			return html_table;
		}
		static string BuildHTMLTableFromDBTable(Table * table)
		{
			Columns * cols = table->GetColumns();
			int cols_count = cols->GetCount();
			int rows_count = table->GetRowsCount();
			string html_table = "";
			
			html_table += "<table border=1>";
			html_table += "<caption> Name: " + table->GetName() + "</br>Rows: " + to_string(rows_count) + " </caption>"; 
			// SET COLUMN NAMES
			html_table += "<tr>";
			for (int i = 0; i < cols_count; i++)
			{
				html_table += "<th>";
				html_table += cols->GetColumnName(i);
				html_table += "</th>";
			}
			html_table += "</tr>";
			// SET ROWS
			for (int i = 0; i < rows_count; i++)
			{
				html_table += "<tr>";
				Row * row = table->GetRow(i);
				for (int k = 0; k < cols_count; k++)
				{
					html_table += "<td>";
					COLUMN_TYPE type = cols->GetColumnType(k);
					switch (type)
					{
						case COLUMN_STRING:
						{
							//string * cur_str_p = (string *)row->GetValue(k); // Strange Behaviour here. Something like memory deallocation. YEP IT WAS TRUE. But fixed
							string cur_str = row->GetString(k);
							html_table += cur_str;
						}break;
						case COLUMN_INT:
						{
							int cur_int = row->GetInt(k);
							html_table += to_string(cur_int);
						}break;
					}
					html_table += "</td>";
				}
				html_table += "</tr>";
			}

			html_table += "</table>";
			return html_table;
		}
};