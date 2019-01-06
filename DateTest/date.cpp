#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

class Date
{
public:
    Date(int y, int m) : year(y), month(m) {}
    bool operator<(const Date& rhs)
    {
        if (year > rhs.year) return false;
        else if (year == rhs.year)
        {
            return month < rhs.month;
        }
        return true;
    }
    int year;
    int month;
};

int main()
{
    Date d1(1999, 12);
    Date d3(2000, 10);
    Date d2(2000, 1);
    Date d4(1997, 9);

    std::vector<Date> dates = { d1, d2, d3, d4 };

    std::sort(dates.begin(), dates.end());

    for (const auto& d : dates)
    {
        std::cout << d.year << " " << d.month << '\n';
    }

    std::getchar();
    return 0;
}