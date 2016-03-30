#pragma once
#include "MainHeaders.h"
namespace Table 
{
	class Row // ONLY STRINGS AND INTS
	{
		struct struct_row_value
		{
			union
			{
				char * string_value;
				int int_value;
			};
		};
	private:
		vector <struct_row_value> values;
	public:
		int GetIntAt(int index)
		{
			return values.at(index).int_value;
		}
		string GetStringAt(int index)
		{
			return string(values.at(index).string_value);
		}

	};
}