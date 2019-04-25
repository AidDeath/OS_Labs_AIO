// LB_04_CLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "LB_04_CLI.h"
#include "../LB_01_DLL_16/LB_01_DLL_16.h"

#pragma comment(lib,"../x64/Debug/LB_01_DLL_16.lib")



int main()
{
	using namespace std;
	SetConsoleTitle(TEXT("Console part"));
	cout << "Work started... \n";
	Sleep(200);
	ifstream reading("in.txt");
	if (!reading.is_open())
	{
		cout << "Unable to read file in.txt\n" << "Exit...\n";
		return(0);
	}
	char buf[30];
	cout << "Reading file... \n";
	Sleep(200);
	reading >> buf;
	int x = atoi(buf);


	getHex(x, *buf);
	cout << "Library fn executed...\n";
	Sleep(200);
	char result[100];
	Sleep(200);
	cout << "Result for " << x << " is " << buf << endl;;

	ofstream writing("out.txt");
	Sleep(200);
	cout << "Writing result to file...\n";
	if (!writing.is_open())
	{
		Sleep(200);
		cout << "Unable to open output file...\n";
		return(0);
	}
	writing << buf;
//	writing.close;
	
	Sleep(200);
	cout << "Result saved to file...\n";
	Sleep(300);
	cout << "Exiting...\n";
	Sleep(100);

	 return(0);
}
