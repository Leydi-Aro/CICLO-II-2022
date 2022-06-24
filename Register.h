#pragma once
#include "Arbol.h"
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
public:
	Dataset() {
		readTSV("data.csv");
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
			
			

			registros.insertar(Register(anios, nombre, estado, contacto, mes, dia, operacion, problemas, cantidad));
		}
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

	void writeTSV() {
		string t_anios, nombre, estado, contacto, mes, t_dia, operacion, t_problemas, t_cantidad;

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

		registros.insertar(Register(anios, nombre, estado, contacto, mes, dia, operacion, problemas, cantidad));



		cout << "GRACIAS POR REPORTAR TU PROBLEMA, TE ATENDEREMOS PRONTO !! \n";
		system("pause");

		file.close();
	}


};

int main() {

	Dataset ds;

	bool run = true;
	short opcion;
	while (run)
	{
		system("cls");
		cout << "\n\n\n\n\t\t\t\t\t\t      || BIENVENIDO INGRESA TU REPORTE ||" << endl << endl;
		cout << "\n\t\t\t\t\t\t 1. - Mostrar enOrden" << endl;
		cout << "\n\t\t\t\t\t\t 2. - Mostrar preOrden" << endl;
		cout << "\n\t\t\t\t\t\t 3. - Mostrar postOrden" << endl;
		cout << "\n\t\t\t\t\t\t 4. - Ingresar Reporte" << endl;
		cout << "\n\t\t\t\t\t\t 5. - Cantidad" << endl;
		cout << "\n\t\t\t\t\t\t 6. - Salir" << endl;
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
			ds.writeTSV();
			break; }
		case 5: {
			cout << "\n\n" << ds.size();
			_getch();
			break; }
		case 6: {
			run = false;
			break;
		}

		}

	}

	_getch();
	return 0;
}