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
	string nombre;
	string operacion;
public:
	// small dataset w ptr
	Register(void* dummy, int anios = 54, string nombre = "", string estado = "", string contacto = "", string mes = "", 
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
	// big dataset no ptr
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
		readTSV2("Archivos/Dataset/data5k.csv");
		readTSV("Archivos/Dataset/data.csv");
	}
	Dataset() {
		readTSV("Archivos/Dataset/data.csv");
	}
	// smallds
	void readTSV(string name = "", bool header = true) {//campos separados por tab o espacios
		ifstream file(name);
		string reg, t_anios, nombre, estado, contacto, mes, t_dia, operacion, t_problemas, t_cantidad;
		int anios;
		int dia;
		int problemas;
		float cantidad;
		if (header)
			getline(file, reg);
		void* dummy;
		while (file >> t_anios >> nombre >> estado>> contacto>>mes>>t_dia>> operacion>> t_problemas>> t_cantidad) {
			anios = stoi(t_anios);
			dia = stoi(t_dia);
			problemas = stoi(t_problemas);
			cantidad = stof(t_cantidad);
			
			

			registros.insertar(Register(dummy, anios, nombre, estado, contacto, mes, dia, operacion, problemas, cantidad));
		}
	}
	void readTSV2(string name = "", bool header = true) {//campos separados por tab o espacios
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


	//small ds
	void writeTSV() {
		string t_anios, nombre, estado, contacto, mes, t_dia, operacion, t_problemas, t_cantidad;
		void* dummy;


		//------
		int anios;
		int dia;
		int problemas;
		float cantidad;
		//-------

		ofstream file;
		file.open("data.csv", ios::app);

		cout << endl;
		cout << "----COMPLETE SUS DATOS PARA PODER REPORTAR EL PROBLEMA----: " << endl;
		getline(cin, t_anios);
		cout << "Ingrese su EDAD: " << endl;
		getline(cin, t_anios);
		file << t_anios;
		cout << "Ingrese su NOMBRE: " << endl;
		getline(cin, nombre);
		file << "\t";
		file << nombre;
		cout << "Ingrese el ESTADO de prioridad del problema (baja, media, alta, urgente): " << endl;
		getline(cin, estado);
		file << "\t";
		file << estado;
		cout << "Ingrese su CONTACTO (ejemplo: gmail ): " << endl;
		getline(cin, contacto);
		file << "\t";
		file << contacto;
		cout << "Ingrese el MES del problema (ejemplo: mayo): " << endl;
		getline(cin, mes);
		file << "\t";
		file << mes;
		cout << "Ingrese el DIA del problema (ejemplo: 12): " << endl;
		getline(cin, t_dia);
		file << "\t";
		file << t_dia;
		cout << "Ingrese en que OPERACION presento problemas (ejemplo: cambio): " << endl;
		getline(cin, operacion);
		file << "\t";
		file << operacion;
		cout << "Ingrese la cantidad de PROBLEMAS que tuvo al realizar la operacion (ejemplo: 2): " << endl;
		getline(cin, t_problemas);
		file << "\t";
		file << t_problemas;
		cout << "Ingrese la CANTIDAD de cambio realizado (s/ o $$): " << endl;
		getline(cin, t_cantidad);
		file << "\t";
		file << t_cantidad;
		file << "\n";

		anios = stoi(t_anios);
		dia = stoi(t_dia);
		problemas = stoi(t_problemas);
		cantidad = stof(t_cantidad);

		registros.insertar(Register(dummy, anios, nombre, estado, contacto, mes, dia, operacion, problemas, cantidad));



		cout << "GRACIAS POR REPORTAR TU PROBLEMA, TE ATENDEREMOS PRONTO !! \n";
		system("pause");

		file.close();
	}


};

