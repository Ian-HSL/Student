#ifndef MyDate_H
#define MyDate_H

#include <string>
using namespace std;

int Greg2Julian(int month, int day, int year);
void Julian2Greg(int JD, int& month, int& day, int& year);

class MyDate {
	private:
		int day;
		int month;
		int year;

		int julianDate = Greg2Julian(month, day, year);

		string months[12] = { "January", "February", "March", "April", "May", "June",
							"July", "August", "September", "October", "November", "December" };

		string weekDays[7] = { "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday" };

	public:
		MyDate();
		MyDate(int M, int D, int Y);

		void display();
		void increaseDate(int N);
		void decreaseDate(int N);
		int daysBetween(MyDate D);
		int getMonth();
		int getDay();
		int getYear();
		int getJulianDate();
		int dayOfYear();
		string dayName();
		string formatDate();

};
#endif 

