#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	const int IS_PRESENT = 1;
	const int EMP_RATE_PER_HR = 20;
	const int EMP_HRS = 8;
	int dailyWage = 0;
	cout << "Welcome To Employee Wage Computation Problem" << endl;
	srand( time(0) );
	int checkAttendance = rand() % 2 + 1;
	if( IS_PRESENT == checkAttendance )
	{
		dailyWage = EMP_RATE_PER_HR * EMP_HRS;
		cout << "Employee Daily Wagre: " << dailyWage << endl;
	}
	else
	{
		cout << "Employee Is Absent" << endl;
	}
	return 0;
}
