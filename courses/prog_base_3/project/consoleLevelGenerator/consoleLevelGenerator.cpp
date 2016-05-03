// consoleLevelGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <ctime>
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
void generateLevel(int fieldSize, float wallDensity, string path);
int main(int argc, char * argv[])
{
	int fieldSize;
	float wallDensity;
	string path;
	if(argc == 4)
	{
		int fieldSize = atoi(argv[1]);
		if (fieldSize % 2 != 1)
		{
			puts("Field size should be odd!");
			return 1;
		}
		float wallDensity = atof(argv[2]);
		if (wallDensity < 0.0f || wallDensity > 1.0f)
		{
			puts("Wall count density should be between 0 and 1");
			return 1;
		}
		string path(argv[3]);
	}
	else if (argc == 1)
	{
		wallDensity = 0.66f;
		fieldSize = 13;
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
	char * levelArray = new char[fieldSize*fieldSize]();
	output.open(path, fstream::out);
	output << to_string(fieldSize) << "\n";
	int numberOfWalls = wallDensity * (fieldSize * fieldSize);
	for (int i = 0; i < fieldSize * fieldSize; i++)
		levelArray[i] = NOTHING_POS_CODE;
	for (int i = 0; i < numberOfWalls; i++)
	{
		levelArray[rand() % fieldSize + (rand() % fieldSize - 1) * fieldSize] = WALL_POS_CODE;
	}
	levelArray[rand() % fieldSize + (rand() % fieldSize - 1) * fieldSize] = WHITEHOLE_POS_CODE; // wallHole
	levelArray[rand() % fieldSize + (rand() % fieldSize - 1) * fieldSize] = PLAYER_POS_CODE; // playerPos
	// Fill level
	for(int i = 0; i < fieldSize; i++)
	{
		for (int j = 0; j < fieldSize; j++)
		{
			output << levelArray[i + fieldSize * j];
		}
		output << "\n";
	}
}
