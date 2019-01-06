#ifndef _DATE_H_
#define _DATE_H_

#include <tuple>
#include <string>
#include <iostream>
#include <cassert>

#include "Tools.h"
class Date
{
public:
    Date() {}
    Date(int y, int M, int d, int h, int m) : year(y), month(M), day(d), hour(h), minute(m) {}
    Date(std::string string);
    bool operator<(const Date& rhs) const;
    bool operator==(const Date& rhs);
    bool operator>(const Date& rhs);
    bool operator!=(const Date& rhs);
    friend std::ostream& operator<<(std::ostream&, const Date& d);
    static void test();
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << "[" << d.year << '-' << d.month << '-' << d.day << ' ' << d.hour << ':' << d.minute << ']';
    return os;
}


Date::Date(std::string string)
{
    std::vector<std::string> date_time = split(string, ' ');
    std::vector<std::string> date = split(date_time[0], '-');
    year = std::stoi(date[0]);
    month = std::stoi(date[1]);
    day = std::stoi(date[2]);

    std::vector<std::string> time = split(date_time[1], ':');
    hour = std::stoi(time[0]);
    minute = std::stoi(time[1]);
}

bool Date::operator<(const Date& rhs) const
{
    return std::tie(year, month, day, hour, minute) < std::tie(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute);
}

bool Date::operator==(const Date& rhs)
{
    return (this->year == rhs.year && this->month == rhs.month && this->day == rhs.day && this->hour == rhs.hour && this->minute == rhs.minute);
}

bool Date::operator>(const Date& rhs)
{
    return !(*this < rhs) && !(*this == rhs);
}

bool Date::operator!=(const Date& rhs)
{
    return !(*this == rhs);
}

void Date::test()
{
    Date d1(2018, 11, 10, 23, 34);
    Date d2(2018, 11, 10, 23, 33);
    Date d3(2019, 1, 1, 1, 1);
    assert(d2 < d1);
    assert(d1 == d1);
    assert(d3 > d1);
    assert("1518-05-13 00:33" < "1518-05-13 00:33");
}

struct Entry
{
    Date date;
    std::string message;
    bool operator<(const Entry& rhs) const
    {
        return this->date < rhs.date;
    }
};

struct Guard
{
    int id;
    std::vector<std::pair<int, int>> phases;
    int minutes_asleep = 0;
};
#endif