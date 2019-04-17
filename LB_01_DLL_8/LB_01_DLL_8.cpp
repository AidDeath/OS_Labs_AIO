// Dll_2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
//#include <sstream>
#include "LB_01_DLL_8.h"


LB_01_DLL_8_API char& getOct(int x)
{
	char buf[30];
	_itoa_s(x, buf, 8);
	//strcpy_s(out, sizeof(buf), buf);

	return *buf;
}

LB_01_DLL_8_API unsigned int SenseOfExisting()
{
	return 8;
}