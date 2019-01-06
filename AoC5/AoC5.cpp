#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>

constexpr int DIST = 32;
constexpr std::array<char, 26> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

std::string react_sequence(std::string& sequence)
{
    std::vector<int> mark_for_removal(sequence.length(), 0);

    int i = 0;
    int next_index = 0;
    while (i < sequence.length() - 1)
    {
        int j = i + 1;
        while (std::abs(sequence[i] - sequence[j]) == DIST)
        {
            mark_for_removal[i] = 1;
            mark_for_removal[j] = 1;
            sequence[i] = '$';
            sequence[j] = '$';

            while (i > 1 && sequence[i] == '$')
                --i;
            while (sequence[j] == '$' && j < sequence.length() - 1)
                ++j;
        }
        i = j;
    }

    std::string result{};
    for (int i = 0; i < sequence.length(); i++)
    {
        if (!mark_for_removal[i])
            result += (sequence[i]);
    }
    return result;
}

int main()
{
    std::ifstream in("input.txt");
    std::string sequence;

    in.seekg(0, std::ios::end);
    sequence.reserve(in.tellg());
    in.seekg(0, std::ios::beg);

    sequence.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    

    sequence.erase(std::remove(sequence.begin(), sequence.end(), '\n'), sequence.end());

    for (auto c : alphabet)
    {
        std::string reduced_sequence = sequence;
        reduced_sequence.erase(std::remove_if(reduced_sequence.begin(), reduced_sequence.end(), [c](char s) { return std::tolower(s) == c; }), reduced_sequence.end());
        char filename[6];
        sprintf_s(filename, "%c.txt", c);
        filename[5] = '\0';
        std::ofstream output(filename);
        output << reduced_sequence;
        std::string result = react_sequence(reduced_sequence);
        std::cout << c << ": " << result.length() << '\n';
    }

    return 0;
}