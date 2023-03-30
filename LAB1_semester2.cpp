#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

#include "strings_algorithms.h"
#include "deps/input.h"

using namespace std;

int main()
{
	while (true)
	{
		switch (string_algorithms::read_int("Enter task number (1-10)", false))
		{
		case 1:
			string_algorithms::test_task1();
			break;
		case 2:
			string_algorithms::test_task2();
			break;
		case 3:
			string_algorithms::test_task3();
			break;
		case 4:
			string_algorithms::test_task4();
			break;
		case 5:
			string_algorithms::test_task5();
			break;
		case 6:
			string_algorithms::test_task6();
			break;
		case 7:
			string_algorithms::test_task7();
			break;
		case 8:
			string_algorithms::test_task8();
			break;
		case 9:
			string_algorithms::test_task9();
			break;
		case 10:
			string_algorithms::test_task10();
			break;
		default:
			cout << "Invalid task number, try again.";
			break;
		}
		cout << "\n\n";
	}
}