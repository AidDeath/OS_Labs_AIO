#pragma once
// define LB_01_DLL_16_EXPORTS for export
#ifdef LB_01_DLL_16_EXPORTS
#define LB_01_DLL_16_API __declspec(dllexport)
#else 
#define LB_01_DLL_16_API __declspec(dllimport)
#endif
// Обьявить функцию в заголовке

LB_01_DLL_16_API void getHex(int x,char& out);
LB_01_DLL_16_API unsigned int SenseOfExisting();