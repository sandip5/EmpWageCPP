#include <iostream>
#include <ctime>
#include <fstream>
#include <unistd.h>

using namespace std;

struct CalculateEmpWage
{
	void calculate()
	{
		const int IS_FULL_TIME = 1;
        	const int IS_PART_TIME = 2;
        	
		int wagePerHr;
		cout << "Enter Company Per Hour Wage: " << endl;
		cin >> wagePerHr;

        	int monthTotalWorkingDays;
		cout << "Enter Number Of Working Days: " << endl;
		cin >> monthTotalWorkingDays;

        	int maxHoursPerMonth;
		cout << "Enter Maximum Hours For Month: " << endl;
		cin >> maxHoursPerMonth;

        	int totalWorkingDays = 0;
        	int empHrs = 0;
        	int totalEmpHrs = 0;
        	int totalWage = 0;
        	int dayWage = 0;

		int months;
		cout << "Enter Months: " << endl;
		cin >> months;
        	
        	srand( time(0) );

        	while( totalEmpHrs < maxHoursPerMonth * months && totalWorkingDays < monthTotalWorkingDays * months )
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
                	dayWage = empHrs * wagePerHr;

                	fstream fileStream;
                	fileStream.open("emp_wage.txt", ios::out | ios::app);

                	if(fileStream.is_open())
                	{
                        	fileStream << "Day: " << totalWorkingDays << "--->" << "Wage: " << dayWage << endl;
                        	fileStream.close();
                	}
        	}

        	totalWage = totalEmpHrs * wagePerHr;

        	fstream fileStream;
        	fileStream.open("emp_wage.txt", ios::out | ios::app);

        	if(fileStream.is_open())
        	{
                	fileStream << "Employee Total Monthly Wage: " << totalWage << endl;
			fileStream << "<---------------------------------------------------------->" << endl;
                	fileStream.close();
        	}

        	cout << "Employee Total Wage: " << totalWage << endl;

	}
};

int main()
{
	CalculateEmpWage emp1;
	emp1.calculate();
	sleep(2);
	CalculateEmpWage emp2;
	emp2.calculate();
	return 0;
}
