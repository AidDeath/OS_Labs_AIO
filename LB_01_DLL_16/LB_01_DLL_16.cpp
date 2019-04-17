// Dll_2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
//#include <sstream>
#include "LB_01_DLL_16.h"


LB_01_DLL_16_API void getHex(int x, char& out)
{
	char buf[30];
	_itoa_s(x, buf, 16);
	strcpy_s(&out, sizeof(buf), buf);
}

LB_01_DLL_16_API unsigned int SenseOfExisting()
{
	return 16;
}