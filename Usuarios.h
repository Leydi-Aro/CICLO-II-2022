#pragma once
#include "Lista.h"
#include "Cuenta.h"

class Usuario {
    string nombre;
    Lista<Cuenta*> arch;
public:
    Usuario(string n) :nombre(n) {}
    ~Usuario() {}

    string getname() { return nombre; }

    //------------C R E A C I O N      D E      A R C H I V O S------------ 

    void crearArch(string a = "", string b = "") {      
        if (a != "" && b != "") {
            arch.insertar(new Cuenta(a, b));
        }
        else {
            string archname, archcom;
            float archmon;
            archname = l1("Ingrese el nombre de la Entidad Bancaria: ");
            archcom = l1("Ingrese el tipo de moneda: ");
            cout << "Ingrese el monto de la cuenta"<<endl;
            cin >> archmon;
            arch.insertar(new Cuenta(archname, archcom,archmon));
        }
    }
    void mostrarArchivos() {     
        while (arch.It->siguiente != nullptr)
        {
            cout << "\t" << arch.getIt()->getnarch() << endl;
            arch.iterar();
        }
        cout << "\t" << arch.getIt()->getnarch() << endl;
        arch.iterar();
    }
    void CargarArchivos() {
        string nam, com;
        string cadena;
        ifstream archivo("Archivos/Usuarios/" + nombre + ".txt");
        while (getline(archivo, cadena))
        {
            stringstream archMem(cadena);
            getline(archMem, nam, '*');
            getline(archMem, com, '*');
            arch.insertar(new Cuenta(nam, com));
        }
    }
    void GuardarArchivos() {
        arch.resetit();
        ofstream archivo("Archivos/Usuarios/" + nombre + ".txt");
        if (arch.It != nullptr) {
            while (arch.It->siguiente != nullptr)
            {
                archivo << arch.getIt()->getnarch() << '*' << arch.getIt()->getCom() << "\n";
                arch.iterar();
            }archivo << arch.getFin()->getnarch() << '*' << arch.getFin()->getCom();
        }
    }
    void menuUser() {       
        int opcion;
        bool run = true;
        while (run)
        {
            system("cls");
            cout << "Bienvenido a E X C H A N G E " << nombre << "\nA�ada una cuenta bancaria para continuar :D  \n: " << endl;
            if (arch.It != nullptr) mostrarArchivos();
            cout << "1. - Agregar Cuenta" << endl;
            cout << "2. - Seleccionar Cuenta" << endl;
            cout << "3. - Salir" << endl;
            cin >> opcion;
            switch (opcion)
            {
            case 1: {
                crearArch();
                break; }
            case 2: {
                string aux;
                aux = l1("\nEscriba el nombre de la Entidad Bancaria: \n"); cout << endl;
                while (arch.It->siguiente != nullptr)
                {
                    if (l2(aux, arch.getIt()->getnarch())) {
                        arch.getIt()->menu();
                        break;
                    }
                    else arch.iterar();
                }
                if (l2(aux, arch.getFin()->getnarch())) arch.getFin()->menu();
                else cout << "\nNombre de archivo no valido";
                arch.resetit();
                break; }
            case 3: {
                run = false;
                break; }
            }
        }
    }
};
