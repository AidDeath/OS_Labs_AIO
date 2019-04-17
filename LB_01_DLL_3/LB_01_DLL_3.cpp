// LB_01_DLL_3.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
//#include <sstream>
#include "LB_01_DLL_3.h"


LB_01_DLL_3_API char* getThree(int x)
{
	char buf[30];
	_itoa_s(x, buf, 3);

	return buf;
}

LB_01_DLL_3_API unsigned int SenseOfExisting()
{
	return 3;
}