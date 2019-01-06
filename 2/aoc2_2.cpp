#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>

bool sortbysec(const std::pair<int,int> &a, 
              const std::pair<int,int> &b) 
{ 
    return (a.second < b.second); 
} 

auto find_close_match(std::vector<std::string> lines)
{
    for (int i = 0; i < (int)lines.size(); ++i)
    {
        for (int j = i+1; j < (int)lines.size(); j++)
        {
            bool mismatchedOnce = false;
            // std::cout << "Comparing: " << lines[i] << " and " << lines[j] << '\n';
            for (int k = 0; i < lines[i].size(); k++)
            {
                if (lines[i][k] != lines[j][k])
                {
                    if (mismatchedOnce) break;
                    mismatchedOnce = true;
                }
            }
            return std::pair<std::string, std::string>(lines[i], lines[j]);
        }
    }
}


int main()
{
    std::ifstream file("test.txt");
    std::vector<std::string> lines;
    std::vector<std::pair<int,int>> line_checksums;
    std::string line;
    int index = 0;
    while (std::getline(file, line))
        lines.push_back(line);

    auto match = find_close_match(lines);

    std::cout << match.first << "\t" << match.second << "\n";

    return 0;

}