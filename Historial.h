#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include "Vector.h"

using namespace std;

class Historial {
public:
    string nombre;
    long long DNI;
    string banco;
    Historial(string nombre = "", long long DNI = 0, string banco = "") :nombre(nombre), DNI(DNI), banco(banco) {

    }

    friend ostream& operator<<(ostream& os, const Historial& e) {
        os << e.nombre << " " << e.DNI << " " << e.banco << endl;
        return os;
    }

    bool operator<(const Historial& e)const {
        return this->DNI < e.DNI;
    }

    bool operator>(const Historial& e)const {
        return this->DNI > e.DNI;
    }



};