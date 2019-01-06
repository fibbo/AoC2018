#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

int main()
{
	std::ifstream f = std::ifstream("2.txt");

	std::string line;

	std::map<char, int> frequency;
	int twice = 0;
	int thrice = 0;
	while (f >> line)
	{

		for (auto c : line) { 
			auto it = frequency.find(c);
			if (it != frequency.end())
			{
				frequency[c] += 1;
			}
			else
			{
				frequency.insert(std::make_pair(c, 1));
			}
		}
		
		bool alreadyTwice = false;
		bool alreadyThrice = false;
		for (auto kv : frequency)
		{
			
			if (!alreadyTwice && kv.second == 2)
			{
				++twice;
				alreadyTwice = true;
			}
			else if (!alreadyThrice && kv.second == 3)
			{
				++thrice;
				alreadyThrice = true;
			}
		}
		frequency.clear();
	}
	std::cout << twice * thrice << '\n';
	f.close();
	return 0;
}