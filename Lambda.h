#pragma once
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <vector>
using namespace std;

auto l1 = [](string s) {cin.get(); cout << endl << s << endl; getline(cin, s); return s;};
auto l2 = [](string a, string b) { return  a == b ? true : false; };
