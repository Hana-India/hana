#include <iostream>
using namespace std;
int main()
{
	system("bin\\MinGW64\\bin\\g++.exe -std=c++11 src\\translator.cpp -o bin\\hanac.exe");
	system("cls");
	cout << "Hana Installation Successful!" << endl;
}
