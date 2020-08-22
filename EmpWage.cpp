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
	int totalWorkingDays;
        int maxHoursPerMonth;
	int totalWage;
	int months;
	vector<int> storeDailyWage;
	vector<int> monthWage;

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

	void setTotalWorkingDays(int totalWorkingDays)
	{
		this -> totalWorkingDays = totalWorkingDays;
	}

	int getTotalWorkingDays()
	{
		return totalWorkingDays;
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

	void setMonthWage(vector<int> storeMonthWage)
        {
                this -> monthWage = storeMonthWage;
        }

        vector<int> getMonthWage()
        {
                return monthWage;
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
		vector<int> storeMonthWage;

		const int IS_FULL_TIME = 1;
	        const int IS_PART_TIME = 2;

		int totalWorkingDays = 0;
        	int empHrs = 0;
        	int totalEmpHrs = 0;
        	int totalWage = 0;
        	int dayWage = 0;
    		int monthWage = 0;
		int monthFactor = 1;
		int perMonthWage = 0;

        	srand( time(0) );

		fstream fileStream;
        	fileStream.open("emp_wage.csv", ios::out | ios::app);

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
			storeDayWage.push_back(dayWage);

			if(companyEmpWage.getMonthTotalWorkingDays() * monthFactor == totalWorkingDays)
			{
				perMonthWage = totalWage - monthWage;
				storeMonthWage.push_back(perMonthWage);
				monthWage = totalWage;
				monthFactor++;
			}

                	if(fileStream.is_open())
                	{
                        	fileStream << totalWorkingDays << "," << companyEmpWage.getCompanyName() << "," << companyEmpWage.getEmployeeName() << ","
				 << dayWage << "," << totalWage << endl;
                	}
        	}

		fileStream.close();

        	totalWage = totalEmpHrs * companyEmpWage.getWagePerHr();

		companyEmpWage.setTotalEmpWage(totalWage);	
		companyEmpWage.setTotalWorkingDays(totalWorkingDays);
		companyEmpWage.setDailyWage(storeDayWage);
		companyEmpWage.setMonthWage(storeMonthWage);

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
			<< container[i].getMonthWage()[sortMonth] << endl;
	}
}

void sortByMonthlyWage(vector<CompanyEmpWage> container, int sortMonth)
{
	cout << "================================== Sort By Month Wage ===================================" << endl;
	cout << "Before Sorting: " << endl;
	printSortingMonthlyWage(container, sortMonth);
	CompanyEmpWage temp;

	for( int i = 0; i < container.size(); i++ )
	{
		int flag = 0;
		for( int j = 0; j < container.size() - 1 - i ; j++ )
		{
			if( container[j].getMonthWage()[sortMonth] <
                        	container[j + 1].getMonthWage()[sortMonth] )
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

void searchEmployee(int wagePerHour, vector<CompanyEmpWage> container)
{
        for(CompanyEmpWage it : container)
        {
                if(it.getWagePerHr() == wagePerHour)
                {
                        cout << "Name Of Employee is: " << it.getEmployeeName() << ", Whose Wage is: "  << it.getWagePerHr() << endl;
                        break;
                }
        }
}

void printSortingDailyWage(vector<CompanyEmpWage> container)
{
        cout << "Company Name" << " : " << "Employee Name" << " : " << "Daily Wage" << endl;

        for(int i = 0; i < container.size(); i++)
        {
                cout << container[i].getCompanyName() << " : " << container[i].getEmployeeName() << " : "
                        << container[i].getWagePerHr() * 8 << endl;
        }
}


void sortByDailyWage(vector<CompanyEmpWage> container)
{
	cout << "================================== Sort By Daily Wage ===================================" << endl;
        cout << "Before Sorting: " << endl;
        printSortingDailyWage(container);
        CompanyEmpWage temp;

        for( int i = 0; i < container.size(); i++ )
        {
                int flag = 0;
                for( int j = 0; j < container.size() - 1 - i ; j++ )
                {
                        if( container[j].getWagePerHr() <
                                	container[j + 1].getWagePerHr() )
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
        printSortingDailyWage(container);
}

int main()
{
	fstream fileStream;
        fileStream.open("emp_wage.csv", ios::out | ios::trunc);
	fileStream << "Day" << "," << "Company Name" << "," << "Employee Name" << "," << "Daily Wage" << "," << "Total Wage" << endl;


	struct CompanyEmpWage empWage[4];
	empWage[0].setDetails( "Apple", "Employee One", 20, 20, 100, 12 );
	empWage[1].setDetails( "Microsoft", "Employee Two", 50, 29, 120, 12 );
	empWage[2].setDetails( "Amazon", "Employee Three", 15, 16, 190, 12 );
	empWage[3].setDetails( "Google", "Employee Four", 100, 24, 148, 12 );

	struct EmpWageAttendance empWageAttendance;
	empWageAttendance.calculateEmpWage(empWage[0]);
	empWageAttendance.calculateEmpWage(empWage[1]);
	empWageAttendance.calculateEmpWage(empWage[2]);
	empWageAttendance.calculateEmpWage(empWage[3]);


	searchTotalWage("Google", empWageAttendance.container);

	cout << "Select a Months In Between 1 to 12 For Which Month You Want To Sort Employees Monthly Wage: " << endl;
	int sortMonth;
	cin >> sortMonth;

	sortByMonthlyWage(empWageAttendance.container, sortMonth);

	sortByDailyWage(empWageAttendance.container);

	return 0;
}
