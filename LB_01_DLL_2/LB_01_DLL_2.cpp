// Dll_2.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
//#include <sstream>
#include "LB_01_DLL_2.h"


LB_01_DLL_2_API void getBin(int x, char* out)
{
	char buf[30];
	_itoa_s(x, buf, 2);
	strcpy_s(out, sizeof(buf), buf);
}

LB_01_DLL_2_API unsigned int SenseOfExisting()
{
	return 2;
}