#pragma once
#include <cstdlib>

#ifdef _WIN32
	#include <conio.h>
#endif

#include "conio.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

auto l1 = [](string s) {cin.get(); cout << endl << s << endl; getline(cin, s); return s;};
auto l2 = [](string a, string b) { return  a == b ? true : false; };
