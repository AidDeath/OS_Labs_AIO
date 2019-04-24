#pragma once

#include "windows.h"
#include <iostream>
#include <fstream>
#include <iostream>



typedef void(*pGetHex)(int x, char&);

pGetHex getHex;