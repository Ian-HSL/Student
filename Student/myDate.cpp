#include "myDate.h"
#include <iostream>
using namespace std;

int Greg2Julian(int month, int day, int year) {

	int i, j, k;

	i = year;
	j = month;
	k = day;

	return k - 32075 + 1461 * (i + 4800 + (j - 14) / 12) / 4 + 367 * (j - 2 - (j - 14) / 12 * 12) 
			/ 12 - 3 * ((i + 4900 + (j - 14) / 12) / 100) / 4;
}

void Julian2Greg(int JD, int& month, int& day, int& year) {
	int i, j, k, l, n;

	l = JD + 68569;
	n = 4 * l / 146097;
	l = l - (146097 * n + 3) / 4;
	i = 4000 * (l + 1) / 1461001;
	l = l - 1461 * i / 4 + 31;
	j = 80 * l / 2447;
	k = l - 2447 * j / 80;
	l = j / 11;
	j = j + 2 - 12 * l;
	i = 100 * (n - 49) + i + l;

	year = i;
	month = j;
	day = k;
}

bool isLeapYear(int year) {
	if ((year % 4 != 0) | ((year % 100 == 0) & (year % 400 != 0))) {
		return false;
	} else {
		return true;
	}
}

// Class Members
MyDate::MyDate() : month(5), day(11), year(1959) {
}

MyDate::MyDate(int M, int D, int Y) : month(M), day(D), year(Y) {
	Julian2Greg(julianDate, month, day, year);

	if ((month != M) & (day != D) & (year != Y)) {
		month = 5, 
		day = 11;
		year = 1959;
	} else {
		month = M;
		day = D;
		year = Y;
	}
	
}

void MyDate::display() {
	cout << months[month - 1] << ' ' << day << ", " << year;
}

void MyDate::increaseDate(int N) {
	int newJulianDate = Greg2Julian(month, day, year) + N;

	Julian2Greg(newJulianDate, month, day, year);

	cout << "Date Increased" << endl;
}

void MyDate::decreaseDate(int N) {
	int newJulianDate = Greg2Julian(month, day, year) - N;

	Julian2Greg(newJulianDate, month, day, year);

	cout << "Date Decreased" << endl;
}

int MyDate::daysBetween(MyDate D) {
	int beginningDate = Greg2Julian(month, day, year);
	int endDate = Greg2Julian(D.month, D.day, D.year);

	return endDate - beginningDate;
}

int MyDate::getMonth() {
	return month;
}

int MyDate::getDay() {
	return day;
}

int MyDate::getYear() {
	return year;
}

int MyDate::getJulianDate() {
	return julianDate;
}

int MyDate::dayOfYear() {
	int dayCount = day;

	if (month == 1) {
		return day;
	}

	for (unsigned int i = 1; i < month; i++) {
		switch (i) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12: {
				dayCount += 31;
				break;
			}
			case 4:
			case 6:
			case 9:
			case 11: {
				dayCount += 30;
				break;
			}
			case 2: {
				if (isLeapYear(year) == true) {
					dayCount += 29;
				} else {
					dayCount += 28;
				}
				break;
			}
		}
	}

	return dayCount;
}

string MyDate::dayName() {
	int dayIndex = Greg2Julian(month, day, year) - Greg2Julian(1, 1, 1970);

	if (dayIndex < 0) {
		dayIndex = 7 - (abs(dayIndex) % 7);
	} else {
		dayIndex = dayIndex % 7;
	}

	return weekDays[dayIndex];
}

string MyDate::formatDate() {
	return months[month - 1] + " " + to_string(day) + ", " + to_string(year);
}