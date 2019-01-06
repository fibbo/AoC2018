#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

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
	Date d1(1999,12);
	Date d3(2000,10);
	Date d2(2000,1);
	Date d4(1997,9);

	std::vector<std::shared_ptr<Date>> dates = {std::make_shared<Date>(d1), std::make_shared<Date>(d2), std::make_shared<Date>(d3), std::make_shared<Date>(d4)};

	// std::sort(dates.begin(), dates.end());

	std::sort(dates.begin(), dates.end(), [](std::shared_ptr<Date> d1, std::shared_ptr<Date> d2) { return *d1 < *d2; });
 

	for (const auto& d : dates)
	{
		std::cout << d->year << " " << d->month << '\n';
	}
	return 0;
}