#pragma once
#include "Arbol.h"
#include "HashTable.hpp"
#include <functional>
#include <math.h>

class Register {
	long anios;
	string trabajo;
	string estado;
	string contacto;
	string mes;
	string dia;
	long cambios;
	long problemas;
	float cantidad;
public:
	Register(long anios = 54, string trabajo = "", string estado = "", string contacto = "", string mes = "", 
		string dia = "", long cambios = 540, long problemas = 3, float cantidad = 5228.1) {
		this->anios = anios;
		this->trabajo = trabajo;
		this->estado = estado;
		this->contacto = contacto;
		this->mes = mes;
		this->dia = dia;
		this->cambios = cambios;
		this->problemas = problemas;
		this->cantidad = cantidad;
	}
	string get_trabajo() {
		return trabajo;
	}
	// funcion hash
	int hash_this() {
		int code = 1e8;
		code += int(cantidad) % 10 * pow(10, 0);
		code += int(anios) % 10 * pow(10, 1);
		code += int(cambios) % 10 * pow(10, 2);
		code += int(problemas) % 10 * pow(10, 3);
		code += int(trabajo.length()) % 10 * pow(10, 4);
		code += int(estado.length()) % 10 * pow(10, 5);
		code += int(contacto.length()) % 10 * pow(10, 6);
		code += int(mes.length()) % 10 * pow(10, 7);
		code += int(dia.length()) % 10 * pow(10, 8);
		return code;
	}
	friend ostream& operator<<(ostream& os, const Register& r) {
		os << r.anios << " " << r.trabajo << " " << r.estado << " " << r.contacto << " " << r.mes << " " << r.dia << " " << r.cambios << " " << r.problemas << " " << r.cantidad<< endl;
		return os;
	}
	bool operator<(const Register& r) {
		return this->anios < r.anios;
	}
	bool operator>=(const Register& r) {
		return this->anios >= r.anios;
	}
	bool operator>(const Register& r) {
		return this->anios > r.anios;
	}
};


class Dataset {
	ArbolB<Register> registros;
	HashTable<Register> hashtable;

public:
	Dataset(function<int(Register)> hash_function) {
		hashtable.set_hash_funcion(hash_function);
		readTSV("Archivos/Dataset/data.csv");
	}
	void readTSV(string name = "", bool header = true) {//campos separados por tab o espacios
		ifstream file(name);
		string reg, t_anios, trabajo, estado, contacto, mes, dia, t_cambios, t_problemas, t_cantidad;
		long anios;
		long cambios;
		long problemas;
		float cantidad;
		if (header)
			getline(file, reg);
		while (file >> t_anios >> trabajo >> estado>> contacto>>mes>>dia>> t_cambios>> t_problemas>> t_cantidad) {
			anios = stoi(t_anios);
			cambios = stoi(t_cambios);
			problemas = stoi(t_problemas);
			cantidad = stof(t_cantidad);

			Register r(anios, trabajo, estado, contacto, mes, dia, cambios, problemas, cantidad);
			registros.insertar(r);
			hashtable.add(r);
		}
	}
	void display_ht(){
		cout << "Registros: " << hashtable.Size() << "\n";
		hashtable.display([](Register r){
			cout << r.get_trabajo(); 	});

	}


	void print() {
		registros.enOrden();
	}
	void printPre() {
		registros.preOrden();
	}
	void printPost() {
		registros.postOrden();
	}
	int size() {
		return registros.cantidad();

	}
};

/*int main() {

	Dataset ds;

	bool run = true;
	short opcion;
	while (run)
	{
		system("clear");
		cout << "\n\n\n\n\t\t\t\t\t\t      || BIENVENIDOS ||" << endl << endl;
		cout << "\n\t\t\t\t\t\t 1. - Mostrar enOrden" << endl;
		cout << "\n\t\t\t\t\t\t 2. - Mostrar preOrden" << endl;
		cout << "\n\t\t\t\t\t\t 3. - Mostrar postOrden" << endl;
		cout << "\n\t\t\t\t\t\t 4. - Cantidad" << endl;
		cout << "\n\t\t\t\t\t\t 5. - Salir" << endl;
		cout << "\n\t\t\t\t\t\t Ingrese un numero: ";
		cin >> opcion;

		switch (opcion) {
		case 1: {
			ds.print();
			_getch();
			break; }
		case 2: {
			ds.printPre();
			_getch();
			break; }
		case 3: {
			ds.printPost();
			_getch();
			break; }
		case 4: {
			cout << "\n\n" << ds.size();
			_getch();
			break; }
		case 5: {
			run = false;
			break;
		}

		}

	}

	_getch();
	return 0;
}*/
