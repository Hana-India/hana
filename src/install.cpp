#include <iostream>
using namespace std;
int main()
{
	system("bin\\MinGW64\\bin\\g++.exe src\\translator-windows.cpp -o bin\\hanac.exe");
	system("cls");
	cout << "Hana Installation Successful!" << endl;
}
