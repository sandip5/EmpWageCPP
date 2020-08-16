#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	const int EMP_RATE_PER_HR = 20;
	const int MONTH_TOTAL_WORKING_DAYS = 20;
	int empHrs = 0;
	int dailyWage = 0;
	int monthWage = 0;

	cout << "Welcome To Employee Wage Computation Problem" << endl;
	srand( time(0) );

	for ( int day = 1; day <= MONTH_TOTAL_WORKING_DAYS; day++ )
	{
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
	monthWage = monthWage + dailyWage;
	}

	cout << "Employee Monthly Wage: " << monthWage << endl;
	return 0;
}
