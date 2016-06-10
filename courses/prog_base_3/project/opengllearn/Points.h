#pragma once

#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct Entry {
	int points;
	string name;
};

class Points {
public:
	Points() {};
	Points(string file);
	Entry getEntry(int index);
	void addEntry(int points);
	void serialize(string file);
private:
	vector<Entry> entries;
};