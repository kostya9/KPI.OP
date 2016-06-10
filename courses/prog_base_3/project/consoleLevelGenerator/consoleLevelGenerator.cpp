// consoleLevelGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define HELP_INFO \
"First argument - size of the field. Should be odd.\n" \
"Second argument - float between 0 and 1 which means walls count density\n" \
"Third argument - output file name\n" \
"The generated level can be not winnable \n" 

#define PLAYER_POS_CODE '3'
#define WHITEHOLE_POS_CODE '2'
#define WALL_POS_CODE '1'
#define NOTHING_POS_CODE '0'

using namespace std;
int validatePos(char * arr, int fieldSize, int index);
void generateLevel(int fieldSize, float wallDensity, string path);
int getRandomPosition(int fieldSize);
int main(int argc, char * argv[])
{
	ofstream test;
	test.open("test.txt");
	test << "started";
	test.close();

	int fieldSize;
	float wallDensity;
	string path;
	if(argc == 4)
	{
		fieldSize = atoi(argv[1]);
		if (fieldSize % 2 != 1)
		{
			puts("Field size should be odd!");
			return 1;
		}
		wallDensity = atof(argv[2]);
		if (wallDensity < 0.0f || wallDensity > 1.0f)
		{
			puts("Wall count density should be between 0 and 1");
			return 1;
		}
		path = string(argv[3]);
	}
	else if (argc <= 1)
	{
		wallDensity = 0.45f;
		fieldSize = 21;
		path = string("output.txt");
	}
	else
	{
		puts(HELP_INFO);
		return 1;
	}
	printf("Generating a level with field %ix%i, wall count density = %.2f, output file : %s\n", fieldSize, fieldSize, wallDensity, path.c_str());
	generateLevel(fieldSize, wallDensity, path);
	puts("Generated successfully");
	return 0;
}
void generateLevel(int fieldSize, float wallDensity, string path)
{
	ofstream output;
	srand(time(NULL));
	char * levelArray = new char[fieldSize*fieldSize + fieldSize*100]();
	output.open(path, fstream::out);
	output << to_string(fieldSize) << "\n";
	int numberOfWalls = static_cast<int>(wallDensity * (fieldSize * fieldSize));
	for (int i = 0; i < fieldSize * fieldSize; i++)
		levelArray[i] = NOTHING_POS_CODE;
	for (int i = 0; i < numberOfWalls; i++)
	{
		int index = getRandomPosition(fieldSize);
		if (levelArray[index] != WALL_POS_CODE && validatePos(levelArray, fieldSize, index))
			levelArray[index] = WALL_POS_CODE;
		else
			i--;
	}
	int index1 = getRandomPosition(fieldSize);
	levelArray[index1] = WHITEHOLE_POS_CODE; // wallHole
	int index;
	do
	{
		index = getRandomPosition(fieldSize);
	} while (index == index1);
	levelArray[index] = PLAYER_POS_CODE; // playerPos
	// Fill level
	for(int i = 0; i < fieldSize; i++)
	{
		for (int j = 0; j < fieldSize; j++)
		{
			output << levelArray[i + fieldSize * j];
		}
		output << "\n";
	}
	puts("dfsdf");
	output.flush();
	output.close();
	delete[] levelArray;
	
}

int getRandomPosition(int fieldSize)
{
	int fieldCount = fieldSize * fieldSize;
	int pos = (rand() + 1) % fieldCount;
	_ASSERT(pos < (fieldSize * fieldSize) && pos >= 0);
	return pos;
}
int validatePos(char * arr, int fieldSize, int index)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (arr[index - fieldSize - 1 + fieldSize * j + i] == WALL_POS_CODE)
				count++;
	if (count > 5)
		return 0;
	return 1;
}