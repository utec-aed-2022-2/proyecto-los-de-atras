#pragma once
#ifndef UNIXTODATE_H
#define UNIXTODATE_H
#include <iostream>
#include <cstring>
#include <string>

std::string unixTimeToHumanReadable(long int seconds)
{
    std::string ans = "";
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int currYear, daysTillNow, extraTime, extraDays, index, date, month, hours, minutes, secondss, flag = 0;

    daysTillNow = seconds / (24 * 60 * 60);
	extraTime = seconds % (24 * 60 * 60);
	currYear = 1970;

    while (true)
    {
		if (currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0))
        {
			if (daysTillNow < 366) { break; }
			daysTillNow -= 366;
		}
		else
        {
            if (daysTillNow < 365) { break; }
			daysTillNow -= 365;
		}
		currYear += 1;
	}

    extraDays = daysTillNow + 1;

    if (currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0)) { flag = 1; }

    month = 0, index = 0;
    if (flag == 1)
    {
		while (true)
        {
			if (index == 1)
            {
				if (extraDays - 29 < 0) { break; }
				month += 1;
				extraDays -= 29;
			}
			else
            {
				if (extraDays - daysOfMonth[index] < 0) { break; }
				month += 1;
				extraDays -= daysOfMonth[index];
			}
			index += 1;
		}
	}
	else
    {
		while (true)
        {
			if (extraDays - daysOfMonth[index] < 0) { break; }
			month += 1;
			extraDays -= daysOfMonth[index];
			index += 1;
		}
	}

    if (extraDays > 0)
    {
		month += 1;
		date = extraDays;
	}
	else
    {
		if (month == 2 && flag == 1) { date = 29; }
		else { date = daysOfMonth[month - 1]; }
	}

    hours = extraTime / 3600;
	minutes = (extraTime % 3600) / 60;
	secondss = (extraTime % 3600) % 60;

	ans += std::to_string(date);
	ans += "/";
	ans += std::to_string(month);
	ans += "/";
	ans += std::to_string(currYear);
	ans += " ";
	ans += std::to_string(hours);
	ans += ":";
	ans += std::to_string(minutes);
	ans += ":";
	ans += std::to_string(secondss);

    return ans;
}

#endif