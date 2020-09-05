#include <iostream>
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
	string comm = argv[1];
	comm="hanac.exe "+comm+".han";
	system(comm.c_str());
	comm = argv[1];
	comm = "MinGW64\\bin\\g++.exe -std=c++11 exec.cpp -o "+comm;
	system(comm.c_str());
}
