#pragma once
class HTMLBuilder
{
	public:
		// With Links
		static string BuildFormNewEntry(Table * table)
		{
			
			string html_form = "";
			html_form += "<html><body>";
			html_form += " <form method=\"get\"> ";
			html_form += "<input type=\"hidden\" name=\"insert\">";
			html_form += "<input type=\"hidden\" name=\"table\" value=\"" + table->GetName() + "\">";
			Columns *cols = table->GetColumns();
			int column_count = cols->GetCount();
			for (int i = 0; i < column_count; i++)
			{
				string cur_column = cols->GetColumnName(i);
				html_form += cur_column + "</br>";
				html_form += " <input type=";
				switch (cols->GetColumnType(i))
				{
					case COLUMN_INT:
					{
						html_form += "\"number\"";
					}break;
					case COLUMN_STRING:
					{
						html_form += "\"text\"";
					}break;
				}
				html_form += " name=\"" + cur_column + "\" > </br>";
			}
			html_form += " <input type=\"submit\" value=\"Submit\"> ";
			html_form += " </form> ";
			html_form += "</body></html>";
			return html_form;
		}
		static string BuildFormEditEntry(Table * table, string key_column, string key_value)
		{
			string html_form = "";
			html_form += "<html><body>";
			html_form += " <form method=\"get\"> ";
			html_form += "<input type=\"hidden\" name=\"edit\">";
			html_form += "<input type=\"hidden\" name=\"key\" value=\"" + key_value + "\">";
			html_form += "<input type=\"hidden\" name=\"table\" value=\"" + table->GetName() + "\">";
			Columns *cols = table->GetColumns();
			int column_count = cols->GetCount();
			for (int i = 0; i < column_count; i++)
			{
				string cur_column = cols->GetColumnName(i);
				if (cur_column == key_column)
					continue;
				html_form += cur_column + "</br>";
				html_form += " <input type=";
				switch (cols->GetColumnType(i))
				{
				case COLUMN_INT:
				{
					html_form += "\"number\"";
				}break;
				case COLUMN_STRING:
				{
					html_form += "\"text\"";
				}break;
				}
				html_form += " name=\"" + cur_column + "\" > </br>";
			}
			html_form += " <input type=\"submit\" value=\"Submit\"> ";
			html_form += " </form> ";
			html_form += "</body></html>";
			return html_form;
		}
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
				html_table += "<a href=\"\\?get&table=" + table_name + "\">"; //LINK TO TABLES
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
			html_table += "<a href=\"\\?form_new&table=" + table->GetName() + "\">" + "NEW ENTRY</a>";
			html_table += "<table border=1>";
			html_table += "<caption> Name: " + table->GetName() + "</br>Rows: " + to_string(rows_count) + " \nLIMIT 100</caption>"; 
			// SET COLUMN NAMES
			html_table += "<tr>"; // Buttons
			html_table += "<th>";
			html_table += "delete";
			html_table += "</th>";
			html_table += "<th>";
			html_table += "edit";
			html_table += "</th>";
			for (int i = 0; i < cols_count; i++)
			{
				html_table += "<th>";
				html_table += cols->GetColumnName(i);
				html_table += "</th>";
			}
			html_table += "</tr>";
			// SET ROWS

			string key = table->GetKey();
			for (int i = 0; i < rows_count; i++)
			{
				Row * row = table->GetRow(i);
				int k = cols->GetColumnIndex(key);
				int cur_key = row->GetInt(k);

				html_table += "<tr>";
				html_table += "<td>";
				html_table += "<a href=\"\\?delete&table=" + table->GetName() + "&key=" + to_string(cur_key) + "\">"; //LINK TO TABLES
				html_table += "delete";
				html_table += "</a>";
				html_table += "</td>";
				html_table += "<td>";
				html_table += "<a href=\"\\?form_edit&table=" + table->GetName() + "&key=" + to_string(cur_key) + "\">"; //LINK TO TABLES
				html_table += "edit";
				html_table += "</a>";
				html_table += "</td>";
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