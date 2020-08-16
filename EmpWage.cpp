#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	const int EMP_RATE_PER_HR = 20;
	int empHrs;
	int dailyWage = 0;

	cout << "Welcome To Employee Wage Computation Problem" << endl;
	srand( time(0) );
	int checkAttendance = rand() % 3 + 1;

	if( IS_FULL_TIME == checkAttendance )
	{
		empHrs = 8;
	}
	else if( IS_PART_TIME == checkAttendance )
	{
		empHrs = 4;
	}
	else
	{
		empHrs = 0;
	}

	dailyWage = EMP_RATE_PER_HR * empHrs; 
	cout << "Employee Daily Wage: " << dailyWage << endl;
	return 0;
}
