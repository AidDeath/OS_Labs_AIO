#pragma once
// define LB_01_DLL_3_EXPORTS for export
#ifdef LB_01_DLL_3_EXPORTS
#define LB_01_DLL_3_API __declspec(dllexport)
#else 
#define LB_01_DLL_3_API __declspec(dllimport)
#endif
// �������� ������� � ���������

LB_01_DLL_3_API char* getThree(int x);
LB_01_DLL_3_API unsigned int SenseOfExisting();