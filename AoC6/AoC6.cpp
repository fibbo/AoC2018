#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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