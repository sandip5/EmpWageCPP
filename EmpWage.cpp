#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	const int IS_FULL_TIME = 1;
	const int IS_PART_TIME = 2;
	const int EMP_RATE_PER_HR = 20;
	const int MONTH_TOTAL_WORKING_DAYS = 20;
	const int MAX_HRS_MONTH = 100;

	int totalWorkingDays = 0;
	int empHrs = 0;
	int totalEmpHrs = 0;
	int totalWage = 0;
	int dayWage = 0;

	cout << "Welcome To Employee Wage Computation Problem" << endl;
	srand( time(0) );

	while( totalEmpHrs < MAX_HRS_MONTH && totalWorkingDays < MONTH_TOTAL_WORKING_DAYS )
	{
		totalWorkingDays++;
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
		
		totalEmpHrs = totalEmpHrs + empHrs;
		dayWage = empHrs * EMP_RATE_PER_HR;

		fstream fileStream;
		fileStream.open("emp_wage.txt", ios::out | ios::app);
		
		if(fileStream.is_open()) 
		{
			fileStream << "Day: " << totalWorkingDays << "--->" << "Wage: " << dayWage << endl;
			fileStream.close();
		}
	}

	totalWage = totalEmpHrs * EMP_RATE_PER_HR;
	
	fstream fileStream;
        fileStream.open("emp_wage.txt", ios::out | ios::app);

        if(fileStream.is_open())
        {
                fileStream << "Employee Total Monthly Wage: " << totalWage << endl;
                fileStream.close();
        }

	cout << "Employee Total Wage: " << totalWage << endl;
	return 0;
}
