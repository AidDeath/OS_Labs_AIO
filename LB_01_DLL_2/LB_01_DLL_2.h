#pragma once
// define LB_01_DLL_2_EXPORTS for export
#ifdef LB_01_DLL_2_EXPORTS
#define LB_01_DLL_2_API __declspec(dllexport)
#else 
#define LB_01_DLL_2_API __declspec(dllimport)
#endif
// �������� ������� � ���������

LB_01_DLL_2_API void getBin(int x,char* out);
LB_01_DLL_2_API unsigned int SenseOfExisting();