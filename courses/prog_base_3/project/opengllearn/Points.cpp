#define _CRT_SECURE_NO_WARNINGS
#include "Points.h"

#include <fstream>
#include <cstring>
#include <cstdio>
bool entryOrder(Entry l, Entry r);
Points::Points(string file)
{
	fstream in;
	in.open(file, fstream::in);
	char curLine[100];
	string line;
	while (getline(in, line))
	{
		if (line.size() < 2)
			continue;
		Entry e;
		strcpy_s(curLine, line.c_str());
		char * tok = strtok(curLine, " ");
		e.name = string(tok);
		tok = strtok(NULL, " ");
		e.points = atoi(tok);
		entries.push_back(e);
	}
	sort(entries.begin(), entries.end(), entryOrder);
	
}
bool entryOrder(Entry l, Entry r)
{
	return l.points > r.points;
}
Entry Points::getEntry(int index)
{
	Entry out;
	try {
		out = entries.at(index);
	}
	catch (out_of_range)
	{
		out.name = "";
		out.points = 0;
	}
	return out;

}

void Points::addEntry(int points)
{
	Entry e;
	e.name = "Default";
	e.points = points;
	entries.push_back(e);
	sort(entries.begin(), entries.end(), entryOrder);
}

void Points::serialize(string file)
{
	fstream out;
	out.open(file, fstream::out);
	int count = entries.size();
	for (int i = 0; i < count; i++)
	{
		Entry cur = entries.at(i);
		out << cur.name << " " << cur.points << "\n";
	}
	out.close();

}
