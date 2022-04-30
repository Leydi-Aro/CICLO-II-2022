#pragma once
#pragma once
#include "Usuarios.h"
#include "Vector.h"
template <typename Tipo>
class Controladora {
	Lista<Tipo*> U;
public:
	Controladora() {}
	~Controladora() {}
	
	//-------------- CONTROLADORA          U  S  U  A  R  I  O-------------------

	void CrearUsuario(string a = "") {
		if (a != "") U.insertar(new Tipo(a));
		else {
			string uname;
			uname = l1("Ingrese nombre del nuevo usuario");
			U.insertar(new Tipo(uname));
		}
	}
	void CargarUsuarios() {
		string linea;
		ifstream arch("Archivos/Usuarios/Usuarios.txt");
		while (getline(arch, linea))
		{
			U.insertar(new Tipo(linea));
		}
		U.resetit();
		while (U.It->siguiente != nullptr)
		{
			if (U.It == nullptr) break;
			U.getIt()->CargarArchivos();
			U.iterar();
		}U.getFin()->CargarArchivos();
	}
	void GuardarUsuarios() {
		U.resetit();
		ofstream arch("Archivos/Usuarios/Usuarios.txt");
		while (U.It->siguiente != nullptr)
		{
			arch << U.getIt()->getname() << "\n";
			U.iterar();
		}arch << U.getFin()->getname();
	}

	void SelecUsuario() {
		U.resetit();
		string temp = l1("\nIngresar nombre del usuario a seleccionar : ");
		while (U.It->siguiente != nullptr)
		{
			if (U.getIt()->getname() == temp) { U.getIt()->menuUser(); break; }
			U.iterar();
		} if (U.getFin()->getname() == temp) U.getFin()->menuUser();
	}
	void mostrarUsuarios() {  
		U.resetit();
		while (U.It->siguiente != nullptr)
		{
			cout << "\t" << U.getIt()->getname() << endl;
			U.iterar();
		}
		cout << "\t" << U.getIt()->getname() << endl;
	}

	//-----------------------------------------------------------------------------
	void menu() {
		bool run = true;
		short opcion;
		while (run)
		{
			system("cls");
			cout << " ||||||||||||||||||| B I E N V E N I D O S   A |||||||||||||" << endl;
			cout << "                       $$ E X C H A N G E $$              " << endl;
			cout << "                        " << endl;
			cout << "Nuestros usuarios:" << endl;
			if (U.It != nullptr) mostrarUsuarios();
			cout << "1. - Crear nuevo usuario" << endl;
			cout << "2. - Seleccionar usuario " << endl;
			cout << "3. - Visualizar cambio sin cuenta" << endl;
			cout << "4. - Salir" << endl;
			cin >> opcion;

			switch (opcion)
			{
			case 1: {
				CrearUsuario();
				break; }
			case 2: {
				SelecUsuario();
				break;
			}
			case 3: {
				Vector<float> dolarvalores;
            	dolarvalores.pushback(3.7180);
            	dolarvalores.pushback(3.7480);
				float dinero = 0;
				float cambio = 0;

				cout << "       Menu de OPERACIONES " << endl;
				cout << "Dolar compra: " << dolarvalores.pos(0) << "  Dolar venta: " << dolarvalores.pos(1) << endl;
				cout << "\n �Que operacion de cambio deseas realizar?";
				cout << "\n 1. Cambio de soles a dolares";
				cout << "\n 2. Cambio de dolares a soles";
				cout << "\n 3. Salir";
				cout << "\n";
				cin >> opcion;

				switch (opcion) {
				case 1:
					cout << "Ingrese la cantidad de soles a cambiar: ";
					cin >> dinero;
					cambio = dinero / (dolarvalores.pos(1));
					cout << "Su cambio es: " << cambio << " dolares";
					break;
				case 2:
					cout << "Ingrese la cantidad de dolares a cambiar: ";
					cin >> dinero;
					cambio = dinero * (dolarvalores.pos(0));

					cout << "Su cambio es: " << cambio  << " soles";
					break;
				case 3:
					cout << "Gracias por usar EXCHANGE";
					break;
				}
				getch();
				break;
			}
			case 4: {
				GuardarUsuarios();
				U.resetit();
				while (U.It->siguiente != nullptr)
				{
					if (U.It == nullptr) break;
					U.getIt()->GuardarArchivos();
					U.iterar();
				}U.getFin()->GuardarArchivos();
				run = false;
				break;
			}
			}
		}
	}
};