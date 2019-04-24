// LB_04_CLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "LB_04_CLI.h"



int main()
{
	using namespace std;
	cout << "Work started... \n";
	ifstream reading("buffer.txt");
	if (!reading.is_open())
	{
		cout << "Unable to read file buffer.txt\n" << "Exit...\n";
		return(0);
	}
	char buf[30];
	cout << "Reading file... \n";
	reading >> buf;
	int x = atoi(buf);

	
	HINSTANCE hLib = LoadLibrary(TEXT("..\\x64\\Debug\\LB_01_DLL_2.dll"));
	if (hLib == NULL)
	{
		cout << "Library is not loaded... \n";
		return(0);
	}
	else
	{
		getHex = (pGetHex)GetProcAddress(hLib, "getHex");
		cout << "Library loaded...\n";
	}

	cout << "Lib fn prepared...\n";
	getHex(x, *buf);
	cout << "Lib fn executed...\n";
	TCHAR result[200];
	wsprintf(result, TEXT("Результат: %s"), buf);
	cout << "Printing result...\n";
	cout << result << endl;
}
