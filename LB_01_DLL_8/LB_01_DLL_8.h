#pragma once
// define LB_01_DLL_8_EXPORTS for export
#ifdef LB_01_DLL_8_EXPORTS
#define LB_01_DLL_8_API __declspec(dllexport)
#else 
#define LB_01_DLL_8_API __declspec(dllimport)
#endif
// Обьявить функцию в заголовке

LB_01_DLL_8_API char& getOct(int x);
LB_01_DLL_8_API unsigned int SenseOfExisting();