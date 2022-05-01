#pragma once
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <functional>
#include <sstream>

// En caso estemos en visual studio incluira conio.h
// Sino incluira conio.hpp
#if _MSC_VER && !__INTEL_COMPILER
	#include <conio.h>
#else
	#include "conio.hpp"
#endif

// Si estamos en windows, CLEAR sera 'cls'
// Sino, CLEAR sera 'clear
#if defined(WIN32)
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif

#include <iomanip>
#include <vector>
using namespace std;

auto l1 = [](string s) {cin.get(); cout << endl << s << endl; getline(cin, s); return s;};
auto l2 = [](string a, string b) { return  a == b ? true : false; };
