#pragma once
#include "Arbol.h"

#include "HashTable.hpp"
#include <functional>
#include <math.h>

class Register {
	int anios;
	string nombre;
	string estado;
	string contacto;
	string mes;
	int dia;
	string operacion;
	int problemas;
	float cantidad;
public:
	Register(int anios = 54, string nombre = "", string estado = "", string contacto = "", string mes = "", 
		int dia = 11, string operacion = "", int problemas = 3, float cantidad = 5228.1) {
		this->anios = anios;
		this->nombre = nombre;
		this->estado = estado;
		this->contacto = contacto;
		this->mes = mes;
		this->dia = dia;
		this->operacion = operacion;
		this->problemas = problemas;
		this->cantidad = cantidad;
	}
	string get_trabajo() {
		return trabajo;
	}

	int hash_this() {
		int code = 1e8; // 1122322 % 5
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
		os << r.anios << " " << r.nombre << " " << r.estado << " " << r.contacto << " " << r.mes << " " << r.dia << " " << r.operacion << " " << r.problemas << " " << r.cantidad<< endl;
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
		string reg, t_anios, nombre, estado, contacto, mes, t_dia, operacion, t_problemas, t_cantidad;
		int anios;
		int dia;
		int problemas;
		float cantidad;
		if (header)
			getline(file, reg);
		while (file >> t_anios >> nombre >> estado>> contacto>>mes>>t_dia>> operacion>> t_problemas>> t_cantidad) {
			anios = stoi(t_anios);
			dia = stoi(t_dia);
			problemas = stoi(t_problemas);
			cantidad = stof(t_cantidad);

			Register r(anios, trabajo, estado, contacto, mes, dia, cambios, problemas, cantidad);
			registros.insertar(r);
			hashtable.add(r);
		}
	}
	void display_ht(){
		cout << "Registros: " << hashtable.Size() << "\n";
		hashtable.display_short([](Register r){
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

