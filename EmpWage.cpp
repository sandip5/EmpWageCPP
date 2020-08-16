#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	cout << "Welcome To Employee Wage Computation Problem" << endl;
	srand( time(0) );
	int checkAttendance = rand() % 2 + 1;
	if( checkAttendance == 1 )
	{
		cout << "Employee Is Present" << endl;
	}
	else if( checkAttendance == 2 )
	{
		cout << "Employee Is Absent" << endl;
	}
	return 0;
}
