#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/************************************************************************/
/* Advent of Code 2018													*/
/* https://adventofcode.com/2018/day/6                                  */
/************************************************************************/


struct Point
{
	int x;
	int y;
};

int main()
{
	std::ifstream file("input.txt");

	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << "\n";
	}

	std::getchar();
}