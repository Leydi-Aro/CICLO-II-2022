#pragma once
#include <iostream>
#include <cstdlib>
#include <functional>
using namespace std;

template <typename Tipo>
struct Nodo {
    Tipo elemento;
    Nodo<Tipo>* siguiente;
    Nodo(Tipo e) { elemento = e; siguiente = nullptr; }
};
template <typename Tipo>
class Lista {
    Nodo<Tipo>* inicio;
    Nodo<Tipo>* fin;
public:
    Lista() {
        It = fin = inicio = nullptr;
    }
    Nodo<Tipo>* It;              
    void insertar(Tipo e) {      
        Nodo<Tipo>* n = new Nodo<Tipo>(e);
        if (inicio == nullptr)
            It = inicio = fin = n;
        else {
            fin->siguiente = n;
            fin = n;
        }
    }
    void mostrar() {
        Nodo<Tipo>* aux = inicio;
        while (aux->siguiente != nullptr) {
            cout << aux->elemento << " ";
            aux = aux->siguiente;
        }
        cout << aux->elemento << " ";
    }          

    void iterar() { if (It->siguiente != nullptr) It = It->siguiente; else It = inicio; }
    void resetit() { It = inicio; }         
    Tipo getIt() { return It->elemento; }   
    Tipo getFin() { return fin->elemento; } 
};
