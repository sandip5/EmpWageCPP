#include <iostream>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <vector>

using namespace std;

struct CompanyEmpWage
{
	private:
	string employeeName;
	string companyName;
	int wagePerHr;
        int monthTotalWorkingDays;
        int maxHoursPerMonth;
	int totalWage;
	int months;
	vector<int> storeDailyWage;

	public:
	void setDetails( string companyName, string employeeName, int wagePerHr, int monthTotalWorkingDays, int maxHoursPerMonth, int months )
	{
		this -> employeeName = employeeName;
		this -> companyName = companyName;
		this -> wagePerHr = wagePerHr;
		this -> monthTotalWorkingDays = monthTotalWorkingDays;
		this -> maxHoursPerMonth = maxHoursPerMonth;
		this -> months = months;
	}

	string getEmployeeName()
	{
		return employeeName;
	}
	
        string getCompanyName()
        {
                return companyName;
        }

        int getWagePerHr()
        {
                return wagePerHr;
        }

        int getMonthTotalWorkingDays()
        {
                return monthTotalWorkingDays;
        }

        int getMaxHoursPerMonth()
	{
                return maxHoursPerMonth;
        }

        int getTotalWage()
        {
                return totalWage;
        }


	void setTotalEmpWage( int totalWage )
	{
		this -> totalWage = totalWage;
	}

	int getMonths()
	{
		return months;
	}

	void setDailyWage(vector<int> storeDayWage)
	{
		this -> storeDailyWage = storeDayWage;
	}
	
	vector<int> getDailyWage()
	{
		return storeDailyWage;
	}
};

struct EmpWageAttendance
{
	vector<CompanyEmpWage> container;
	void addCompany(CompanyEmpWage companyEmpWage)
	{
        	container.push_back(companyEmpWage);
	}

	void calculateEmpWage(CompanyEmpWage companyEmpWage)
	{
		vector<int> storeDayWage;

		const int IS_FULL_TIME = 1;
	        const int IS_PART_TIME = 2;

		int totalWorkingDays = 0;
        	int empHrs = 0;
        	int totalEmpHrs = 0;
        	int totalWage = 0;
        	int dayWage = 0;
		int monthFactor = 1;
	
        	srand( time(0) );

		fstream fileStream;
        	fileStream.open("emp_wage.csv", ios::out | ios::app);
        	fileStream << "Day" << "," << "Company Name" << "," << "Employee Name" << "," << "Daily Wage" << "," << "Total Wage" << endl;

      
        	while( totalEmpHrs < companyEmpWage.getMaxHoursPerMonth() * companyEmpWage.getMonths() &&
			 totalWorkingDays < companyEmpWage.getMonthTotalWorkingDays() * companyEmpWage.getMonths() )
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
                	dayWage = empHrs * companyEmpWage.getWagePerHr();
			totalWage = totalEmpHrs * companyEmpWage.getWagePerHr();
			storeDayWage.push_back(totalWage);

                	if(fileStream.is_open())
                	{
                        	fileStream << totalWorkingDays << "," << companyEmpWage.getCompanyName() << "," << companyEmpWage.getEmployeeName() << ","
				 << dayWage << "," << " " << endl;
                	}
        	}

        	totalWage = totalEmpHrs * companyEmpWage.getWagePerHr();
		companyEmpWage.setTotalEmpWage(totalWage);

		companyEmpWage.setDailyWage(storeDayWage);
	
        	if(fileStream.is_open())
        	{
                	fileStream << " " << "," << " " << "," << " " << "," << " " << "," << totalWage << endl;
                	fileStream.close();
        	}

        	cout << "Employee Total Wage: " << companyEmpWage.getTotalWage() << endl;
		addCompany(companyEmpWage);
	}
};

void searchTotalWage(string companyName, vector<CompanyEmpWage> container)
{
	for(CompanyEmpWage it : container)
	{
		if(it.getCompanyName() == companyName)
		{
			cout << "Total Wage: " << it.getTotalWage() << endl;
			break;
		}
	}
}

void printSortingMonthlyWage(vector<CompanyEmpWage> container, int sortMonth)
{
	cout << "Company Name" << " : " << "Employee Name" << " : " << "Month" << " : " << "Wage" << endl;

	for(int i = 0; i < container.size(); i++)
	{
		cout << container[i].getCompanyName() << " : " << container[i].getEmployeeName() << " : " << sortMonth << " : "
			<< container[i].getDailyWage()[container[i].getMonthTotalWorkingDays() * sortMonth] << endl;
	}
}

void sortByMonthlyWage(vector<CompanyEmpWage> container, int sortMonth)
{
	cout << "Before Sorting: " << endl;
	printSortingMonthlyWage(container, sortMonth);
	CompanyEmpWage temp;

	for( int i = 0; i < container.size(); i++ )
	{
		int flag = 0;
		for( int j = 0; j < container.size() - 1 - i ; j++ )
		{
			if( container[j].getDailyWage()[container[j].getMonthTotalWorkingDays() * sortMonth] <
                        	container[j + 1].getDailyWage()[container[j + 1].getMonthTotalWorkingDays() * sortMonth] )
			{
				temp = container[j];
				container[j] = container[j + 1];
				container[j + 1] = temp;
				flag = 1;
			}
		}
		if(flag == 0) 
		{
			break;
		}
	}

	cout << "After Sorting: " << endl;
        printSortingMonthlyWage(container, sortMonth);
}

int main()
{
	fstream fileStream;
        fileStream.open("emp_wage.csv", ios::out | ios::trunc);

	struct CompanyEmpWage empWage[2];
	empWage[0].setDetails( "Reliance", "Sumeet", 20, 20, 100, 12 );
	empWage[1].setDetails( "Dmart", "Rani", 50, 28, 120, 12 );

	struct EmpWageAttendance empWageAttendance;
	empWageAttendance.calculateEmpWage(empWage[0]);	
	empWageAttendance.calculateEmpWage(empWage[1]);

	searchTotalWage("Reliance", empWageAttendance.container);

	cout << "Select a Months In Between 1 to 12 For Which Month You Want To Sort Employees Monthly Wage: " << endl;
	int sortMonth;
	cin >> sortMonth;

	sortByMonthlyWage(empWageAttendance.container, sortMonth);
	return 0;
}
