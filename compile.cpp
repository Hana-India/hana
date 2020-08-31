/**
THIS CODE IS FOR THE WINDOWS COMPILER.

FOR LINUX COMPILER PLEASE OPEN THE FILE NAMED "compile"
**/
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char **argv)
{
	system(("hanac.exe "+string(argv[1])+".han").c_str());
	system(("C:\\MinGW\\bin\\g++ exec.cpp -o "+string(argv[1])+".exe").c_str());
	system("rm exec.cpp");
}