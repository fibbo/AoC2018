#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

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
            bool cont = false;
#if _DEBUG
            std::cout << "Comparing: " << i << " and " << j << '\n';
#endif
            for (int k = 0; k < lines[i].size(); k++)
            {
                if (lines[i][k] != lines[j][k])
                {
                    if (mismatchedOnce)
                    {
                        cont = true;
                        break;
                    }
                    mismatchedOnce = true;
                }
            }
            if (!cont)
                return std::pair<std::string, std::string>(lines[i], lines[j]);
        }
    }
    return std::pair<std::string, std::string>();
}


int main()
{
    std::ifstream file("2.txt");
    std::vector<std::string> lines;
    std::vector<std::pair<int,int>> line_checksums;
    std::string line;
    int index = 0;
    while (std::getline(file, line))
        lines.push_back(line);

    auto match = find_close_match(lines);

    std::cout << "Matches:\n";

    std::cout << match.first << "\t" << match.second << "\n";

    std::string result;
    for (int i = 0; i < match.first.size(); i++)
    {
        if (match.first[i] == match.second[i])
        {
            result += match.first[i];
        }
    }
    std::cout << result;
    std::getchar();
    return 0;

}