#include<iostream>
using namespace std;
int main()
{
	system("sudo apt-get install git");
	system("sudo apt-get install g++");
	system("sudo apt-get install python3");
	system("sudo apt-get install python3-pip");
	system("g++ translator.cpp -o hanac");
	system("clear");
	system("chmod +x compile");
}
