#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include "Student.cpp"
using namespace std;

/*
	Prototype Functions
*/
void switchElements(Student* roster[], int element1, int element);

void populate(Student** C);

bool compare(Student* student1, Student* student2, int code);

bool equality(Student* student1, Student* student2, int code);

void quickSort(Student* roster[], int begin, int end, int code);

void displayRoster(Student* roster[]);

/*
	Main Program
*/

int main(){
	
	Student* myClass[9];
	populate(myClass);

	Student* original[9];
	for (unsigned int i = 0; i < 9; i++) {
		original[i] = myClass[i];
	}

	int input = 0;

	do {
		cout << "1) Display original list" << endl <<
				"2) Display list sorted by Student ID" << endl <<
				"3) Display list sorted by Name" << endl <<
				"4) Display list sorted by Grade" << endl <<
				"5) Display list sorted by Birthday" << endl <<
				"6) Display list sorted by HomeTown" << endl <<
				"7) Exit" << endl;

		cin >> input;

		switch (input) {
			case 1: {
				displayRoster(original);
				break;
			}
			case 2: {
				quickSort(myClass, 0, 8, input);

				displayRoster(myClass);
				break;
			}
			case 3: {
				quickSort(myClass, 0, 8, input);

				displayRoster(myClass);
				break;
			}
			case 4: {
				quickSort(myClass, 0, 8, input);

				displayRoster(myClass);
				break;
			}
			case 5: {
				quickSort(myClass, 0, 8, input);

				displayRoster(myClass);
				break;
			}
			case 6: {
				quickSort(myClass, 0, 8, input);

				displayRoster(myClass);
				break;
			}
			case 7: {
				break;
			}
			default:
				break;
		}
	} while (input != 7);
	
	getchar();
	return 0;
}

/*
	Helper functions
*/

// Switches the index of two student structs
void switchElements(Student* roster[], int element1, int element2) {
	Student* temp = roster[element1];

	roster[element1] = roster[element2];
	roster[element2] = temp;
}

// Randomly generates the student struct info and inserts into struct array
void populate(Student** C) {
	srand(time(0));

	char grades[5] = { 'A', 'B', 'C', 'D', 'F' };

	for (unsigned int i = 0; i < 9; i++) {
		int randID = (rand() % 900000) + 100000;
		int randMonth = (rand() % 12) + 1;
		int randDay = (rand() % 31) + 1;
		int randYear = (rand() % 6) + 1999;
		int randGrade = rand() % 5;
		MyDate randBirthday(randMonth, randDay, randYear);

		C[i] = new Student();
		C[i]->grade = grades[randGrade];

		switch (i) {
		case 0:
			strcpy_s(C[i]->name, "Ian");
			C[i]->homeTown = "Cypress";
			break;
		case 1:
			strcpy_s(C[i]->name, "Joseph");
			C[i]->homeTown = "Newyork";
			break;
		case 2:
			strcpy_s(C[i]->name, "Jolyne");
			C[i]->homeTown = "Tallahassee";
			break;
		case 3:
			strcpy_s(C[i]->name, "Lucy");
			C[i]->homeTown = "Tallahassee";
			break;
		case 4:
			strcpy_s(C[i]->name, "Eric");
			C[i]->homeTown = "Cypress";
			break;
		case 5:
			strcpy_s(C[i]->name, "Josuke");
			C[i]->homeTown = "Morioh";
			break;
		case 6:
			strcpy_s(C[i]->name, "Koichi");
			C[i]->homeTown = "Morioh";
			break;
		case 7:
			strcpy_s(C[i]->name, "Jotaro");
			C[i]->homeTown = "Tokyo";
			break;
		case 8:
			strcpy_s(C[i]->name, "Kakyoin");
			C[i]->homeTown = "Cairo";
			break;
		default:
			break;
		}

		C[i]->SID = randID;
		C[i]->bday = randBirthday;
	}
}

// Checks whether the specified element in each of the student info are the same
bool equality(Student* student1, Student* student2, int code) {
	switch (code) {
		case 2:
			return student1->SID == student2->SID;
			break;
		case 3:
			return student1->name == student2->name;
			break;
		case 4:
			return student1->grade == student2->grade;
			break;
		case 5:
			return student1->bday.getJulianDate() == student2->bday.getJulianDate();
			break;
		case 6:
			return student1->homeTown.compare(student2->homeTown) == 0;
			break;
		default:
			return 0;
			break;
	}
}

// Helper function that consolidates the comparisons in the quicksort function
// Compares strings and int
bool compare(Student* student1, Student* student2, int code) {
	switch (code) {
		case 2:
			return student1->SID < student2->SID;
			break;
		case 3:
			return strcmp(student1->name, student2->name) > 0;
			break;
		case 4:
			return student1->grade > student2->grade;
			break;
		case 5:
			return student1->bday.getJulianDate() < student2->bday.getJulianDate();
			break;
		case 6:
			return student1->homeTown.compare(student2->homeTown) > 0;
		default:
			break;
	}
}

// Sorts the Student pointer array using the "quick sort" algorithm
void quickSort(Student* roster[], int begin, int end, int code) {

	// If the begin and end indices are the same, the selection has only one element
	if (begin != end) {
		// Record the begin and end indices before using them
		int startIndex = begin;
		int endIndex = end;
		Student* pivot;
		end--;

		// Pivot element recorded
		pivot = roster[endIndex];

		// Keeps looping until the begin and end indices are the same
		while (end != begin) {
			// If the beginning element is less than the pivot, the index is incremented				
			if (compare(roster[begin], pivot, code) || (equality(roster[begin], pivot, code) && equality(roster[end], pivot, code))){ 
				begin++;

			// If the ending element is less than the pivot, the index is decremented
			} else if ((compare(pivot, roster[end], code)) & (begin != end)) { // pivot < roster[end]
				end--;

			// If the ending element is less than pivot
			// and the beginning element is more than the pivot,
			// the switch is made
			} else if ((!compare(roster[begin], pivot, code)) & (!compare(pivot, roster[end], code))) { 
				switchElements(roster, begin, end);														
			}
		}

		if (compare(pivot, roster[end], code)) { 
			switchElements(roster, end, endIndex);
		} else if (end != begin) {
			switchElements(roster, end + 1, endIndex);
		}

		// If the pivot is at the startIndex, do recursive method only on right set
		if (begin == startIndex) {
			quickSort(roster, startIndex + 1, endIndex, code);
			// If the pivot is at the endIndex - 1, do recursive method only on left set
		} else if (end == endIndex - 1) {
			quickSort(roster, startIndex, endIndex - 1, code);
			// Do recursive method on both left and right sets from the pivot
		} else if ((startIndex != endIndex) & (endIndex - startIndex != 1)) {
			quickSort(roster, startIndex, end - 1, code);
			quickSort(roster, end + 1, endIndex, code);
		}
	}
}

// Displays Student Information
void displayRoster(Student* roster[]) {
	cout << left << setw(25) << "Student ID" <<
		setw(25) << "Name" <<
		setw(25) << "Grade" <<
		setw(25) << "Birthday" <<
		setw(25) << "Home Town" << endl;

	for (unsigned int i = 0; i < 9; i++){
		cout << left << setw(25) << roster[8 - i]->SID <<
						setw(25) << roster[8 - i]->name <<
						setw(25) << roster[8 - i]->grade <<
						setw(25) << roster[8 - i]->bday.formatDate() <<
						setw(25) << roster[8 - i]->homeTown << endl;
	}
}