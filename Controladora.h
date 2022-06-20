#pragma once
#include "Usuarios.h"
#include "Vector.h"
#include "Historial.h"
#include "Register.h"
#include "Arbol.h"

template <typename Tipo>
class Controladora
{
	Lista<Tipo *> U;

public:
	Controladora() {}
	~Controladora() {}

	//-------------- CONTROLADORA          U  S  U  A  R  I  O-------------------

	void CrearUsuario(string a = "")
	{
		if (a != "")
			U.insertar(new Tipo(a));
		else
		{
			string uname;
			uname = l1("Ingrese nombre del nuevo usuario");
			U.insertar(new Tipo(uname));
		}
	}
	void CargarUsuarios()
	{
		string linea;
		ifstream arch("Archivos/Usuarios/Usuarios.txt");
		while (getline(arch, linea))
		{
			U.insertar(new Tipo(linea));
		}
		U.resetit();
		while (U.It->siguiente != nullptr)
		{
			if (U.It == nullptr)
				break;
			U.getIt()->CargarArchivos();
			U.iterar();
		}
		U.getFin()->CargarArchivos();
	}
	void GuardarUsuarios()
	{
		U.resetit();
		ofstream arch("Archivos/Usuarios/Usuarios.txt");
		while (U.It->siguiente != nullptr)
		{
			arch << U.getIt()->getname() << "\n";
			U.iterar();
		}
		arch << U.getFin()->getname();
	}

	void SelecUsuario()
	{
		U.resetit();
		string temp = l1("\nIngresar nombre del usuario a seleccionar : ");
		while (U.It->siguiente != nullptr)
		{
			if (U.getIt()->getname() == temp)
			{
				U.getIt()->menuUser();
				break;
			}
			U.iterar();
		}
		if (U.getFin()->getname() == temp)
			U.getFin()->menuUser();
	}
	void mostrarUsuarios()
	{
		// Ordenar por orden alfabetico usando quicksort
		U.quick_sort([](Usuario *a, Usuario *b)
					 { return a->getname() < b->getname(); });
		U.resetit();
		while (U.It->siguiente != nullptr)
		{
			cout << "\t" << U.getIt()->getname() << endl;
			U.iterar();
		}
		cout << "\t" << U.getIt()->getname() << endl;
	}

	string fhash(string name, string monto)
	{
		string cadena;
		cadena = name += monto;

		stringstream ss;
		int i = 0;
		ss << std::hex;
		for (size_t i = 0; i < 8; i++)
		{
			ss << rand() % 16;
		}
		for (size_t i = 0; i < cadena.length(); i++)
		{
			ss << cadena[i] % 16;
		}
		for (size_t i = 0; i < 8; i++)
		{
			ss << rand() % 16;
		}

		string temp;
		for (size_t i = 0; i < 20; i++)
		{
			if (ss.str()[i] != 0)
				temp += ss.str()[i];
			else
				temp += to_string(rand() % 10);
		}
		return temp;
	}
	//-----------------------------------------------------------------------------
	void menu()
	{
		bool run = true;
		short opcion;
		while (run)
		{
			system("cls");
			cout << " ||||||||||||||||||| B I E N V E N I D O S   A |||||||||||||" << endl;
			cout << "                       $$ E X C H A N G E $$              " << endl;
			cout << "                        " << endl;
			cout << "Nuestros usuarios:" << endl;
			if (U.It != nullptr)
				mostrarUsuarios();
			cout << "1. - Reg" << char(161) << "strate" << endl;
			cout << "2. - Inicia sesi" << char(162) << "n" << endl;
			cout << "3. - Visualizar Cambio sin cuenta" << endl;
			cout << "4. - Historial de Usuarios Antiguos" << endl;
			cout << "5. - Tipo de cambio" << endl;
			cout << "6. - Ver Arbol de registros" << endl;
			cout << "7. - Avanze HashTable (HashFunction)" << endl;
			cout << "8. - Salir" << endl;
			cin >> opcion;

			switch (opcion)
			{
			case 1:
			{
				CrearUsuario();
				break;
			}
			case 2:
			{
				SelecUsuario();
				break;
			}
			case 3:
			{
				Vector<float> dolarvalores;
				dolarvalores.pushback(3.7180);
				dolarvalores.pushback(3.7480);

				float dinero = 0;
				float cambio = 0;

				cout << "       Menu de OPERACIONES " << endl;
				cout << "Dolar compra: " << dolarvalores.pos(0) << "  Dolar venta: " << dolarvalores.pos(1) << endl;
				cout << "\n ¿Que operacion de cambio deseas realizar?";
				cout << "\n 1. Cambio de soles a dolares";
				cout << "\n 2. Cambio de dolares a soles";
				cout << "\n 3. Salir";
				cout << "\n";
				cin >> opcion;

				switch (opcion)
				{
				case 1:
					cout << "Ingrese la cantidad de soles a cambiar: ";
					cin >> dinero;
					cambio = dinero / dolarvalores.pos(1);
					cout << "Su cambio es: " << cambio << " dolares";
					break;
				case 2:
					cout << "Ingrese la cantidad de dolares a cambiar: ";
					cin >> dinero;
					cambio = dinero * dolarvalores.pos(0);

					cout << "Su cambio es: " << cambio << " soles";
					break;
				case 3:
					cout << "Gracias por usar EXCHANGE";
					break;
				}
				getch();
				break;
			}
			case 4:
			{
				Vector<Historial> datos;
				datos.pushback(Historial("Claudia", 340000000, "BCP"));
				datos.pushback(Historial("Pedro", 450000000, "INTERBANK"));
				datos.pushback(Historial("Sofia", 120000000, "SCOTIABANK"));
				datos.pushback(Historial("Pablo", 230000000, "BBVA"));
				datos.pushback(Historial("Marcela", 560000000, "BANBIF"));
				datos.pushback(Historial("Roberto", 780000000, "PRESTASUR"));
				datos.pushback(Historial("Valentin", 670000000, "FINANCIERO"));
				datos.pushback(Historial("Xiomara", 890000000, "CONTINENTAL"));

				// auto compare= [](Datos i, Datos j)->bool {return i < j; };
				auto comparar = [](Historial i, Historial j) -> bool
				{ return i > j; };
				auto y = [](Historial c)
				{ cout << c; };

				cout << "-----------H I S T O R I A L    D E    U S U A R I O S----------------" << endl;
				datos.ver(y);

				cout << "----------------ORDENAMINETO BURBUJA-------------------" << endl;
				// cout << "-----------------Ordena a la derecha--------------------" << endl;
				datos.OrdenamientoBurbuja(comparar);
				datos.ver(y);

				cout << "------------------------ORDENAMIENTO INTERCAMBIO----------------" << endl;
				// cout << "-------------------------Ordena a la izquierda--------------------" << endl;
				datos.OrdenamientoIntercambio(comparar);
				datos.ver(y);

				cout << "------------------------ORDENAMIENTO ALEATORIO----------------" << endl;
				// cout << "-------------------------Ordenamiento Fisher-Yates shuffle--------------------" << endl;
				datos.fisher_yates();
				datos.ver(y);

				cout << endl;

				getch();
				break;
			}
			case 5:
			{
				Vector<float> dolarvalores;
				dolarvalores.pushback(3.7180);
				dolarvalores.pushback(3.7480);

				cout << "Precio del d" << char(162) << "lar hoy en Per" << char(163) << endl;
				cout << "\n";

				string myarray[4][3] = {
					"             ", " Compra ", " Venta ",
					"EXCHANGE     ", to_string(dolarvalores.pos(0)), to_string(dolarvalores.pos(1)),
					"Paralelo     ", " 3.7000 ", " 3.7500 ",
					"Bancos       ", " 3.6200 ", " 3.8600 "};

				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						cout << myarray[i][j] << " ";
					}
					cout << endl;
				};

				getch();
				break;
			}
			case 6:
			{

				Dataset ds;
				bool run = true;
				short opcion;
				while (run)
				{
					system("cls");
					cout << "\n\n\n\n\t\t\t\t\t\t      || BIENVENIDOS ||" << endl
						 << endl;
					cout << "\n\t\t\t\t\t\t 1. - Mostrar enOrden" << endl;
					cout << "\n\t\t\t\t\t\t 2. - Mostrar preOrden" << endl;
					cout << "\n\t\t\t\t\t\t 3. - Mostrar postOrden" << endl;
					cout << "\n\t\t\t\t\t\t 4. - Cantidad" << endl;
					cout << "\n\t\t\t\t\t\t 5. - Salir" << endl;
					cout << "\n\t\t\t\t\t\t Ingrese un numero: ";
					cin >> opcion;

					switch (opcion)
					{
					case 1:
					{
						ds.print();
						_getch();
						break;
					}
					case 2:
					{
						ds.printPre();
						_getch();
						break;
					}
					case 3:
					{
						ds.printPost();
						_getch();
						break;
					}
					case 4:
					{
						cout << "\n\n"
							 << ds.size();
						_getch();
						break;
					}
					case 5:
					{
						run = false;
						break;
					}
					}
				}

				getch();
				break;
			}
			case 7:
			{
				string nombre, saldo;

				cout << "        HASH        " << endl;
				cout << "Escriba su nombre: ";
				getline(cin, nombre);

				cout << "Escriba su cantidad de dinero: ";
				getline(cin, saldo);

				// funcionhash(nombre, saldo);

				cout << "\nEl c" << char(162) << "digo hash es el siguiente :" << endl;
				cout << fhash(nombre, saldo);
			}
			case 8:
			{
				GuardarUsuarios();
				U.resetit();
				while (U.It->siguiente != nullptr)
				{
					if (U.It == nullptr)
						break;
					U.getIt()->GuardarArchivos();
					U.iterar();
				}
				U.getFin()->GuardarArchivos();
				run = false;
				break;
			}
			}
		}
	}
};
