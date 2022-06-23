#pragma once
#include "Lambda.h"
#include "Pila.h"
#include "Vector.h"
#include <iomanip>
#include "ExchangeLog.h"


class Cuenta {
    string Banco;
    string Moneda;
    float Monto;
	Pila<Exchange> stack;
public:
    Cuenta(string a, string c = " ", float o=0.0) :Banco(a), Moneda(c), Monto(o) {
        ofstream arch("Archivos/Archivos de Usuarios/" + a + ".txt"); //Cuando se crea un objeto Cuenta, se crea el txt correspondiente
    }
    ~Cuenta() {}
    string getnarch() { return Banco; }
    string getCom() { return Moneda; }
    float getMon() { return Monto; }


    // ----Abrir archivo de cuenta ----
    void abrirArch() {
        system("clear");
        cout << "Imprimiendo datos de la Cuenta " << Banco << ".txt" << endl;
        cout << "Tipo de Moneda: " << Moneda << endl;//cout << "Comentario: " << Moneda << endl;
        cout << "Monto disponible en la cuenta: " << Monto << endl;
        string linea, texto;
        ifstream archivo("Archivos/Archivos de Usuarios/" + Banco + ".txt");
        while (getline(archivo, linea))
        {
            texto = texto + linea;
        }
        cout << texto;
        cin.get();
    }
    //----------------  O   P   E   R   A  C  I   O   N   E   S-----------------
    
    //EXCHANGE VENTA
 void operacionVenta(float valor) {
        float cantidad_venta = 0.0;
        float cambio = 0.0;
        cout << "Ingrese la cantidad a cambiar:" << endl;
        cin >> cantidad_venta;
        cambio = cantidad_venta / valor;
        Monto = Monto - cantidad_venta;
        cout << "Has cambiado " << cantidad_venta << " soles a " << fixed << setprecision(2) << cambio << " dolares" << endl;
		stack.agregar({cambio, cantidad_venta, "USD", "PEN", 1});
        cout << "El saldo en tu cuenta actual es de " << Monto << " soles";
    }
    //EXCHANGE COMPRA
    void operacionCompra(float valor) {
        float cambio = 0.0;
        float cantidad_compra = 0.0;

        cout << "Ingrese la cantidad a cambiar:" << endl;
        cin >> cantidad_compra;
        cambio = cantidad_compra * valor;
        Monto = Monto - cantidad_compra;
        cout << "Has cambiado " << cantidad_compra << " dolares a " << fixed << setprecision(2) << cambio  << " soles" << endl;
		stack.agregar({cambio, cantidad_compra, "PEN", "USD", 0});
        cout << "El saldo en tu cuenta actual es de " << Monto << " dolares";
    }

	void deshacerOperacion() {
		if (stack.Size()) {
			Exchange s = stack.popear().undo();
			cout << "Se le ha devuelto " << s.divisa_compra << " " << setprecision(2) << s.compra << " a su cuenta\n";
			Monto += s.type ? s.venta : s.compra;
		} else {
			cout << "No hay operaciones que deshacer\n";
		}
	}
     
    //------------M   E   N   U       D  E           O   P   E   R   A  C  I   O   N   E   S-----------------
    void menu() {
        int opcion;
        bool run = true;
        while (run)
        {
            system("clear");

            Vector<float> dolarvalores;
            dolarvalores.pushback(3.7180);
            dolarvalores.pushback(3.7480);

            cout << "Nombre del archivo: " << Banco << endl;
            cout << "Tipo de Moneda: " << Moneda << endl << endl;
            cout << "Monto disponible: " << Monto << endl << endl;
            cout << "                         "<<endl;

            cout << "  $$   Realizar Operacion  $$" << endl;
            cout << "-------------------------------------                         " << endl;
            cout << "Dolar compra: " << dolarvalores.pos(0) << "  Dolar venta: " << dolarvalores.pos(1) << endl;
            cout<<  "1. - Visualizar Cuenta" << endl;
            cout << "2. - EXCHANGE--->  Cambio de soles a dolares (VENTA)" << endl;
            cout << "3. - EXCHANGE--->  Cambio de dolares a soles (COMPRA)" << endl;
            cout << "4. - EXCHANGE--->  Deshacer operacion" << endl;

            cout << "5. - Regresar" << endl;
           
            cin >> opcion;
            switch (opcion)
            {
            case 1:
                abrirArch();
                cin.get();
                break;
            case 2:
                operacionVenta(dolarvalores.pos(0));
                getch();
                break;
            case 3:
                operacionCompra(dolarvalores.pos(1));
                getch();
                break;
			case 4:
				deshacerOperacion();
				getch();
				break;
            case 5:
                run = false;
                break;
            }
        }
    }
};
