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
	int len = 0;
public:
    Lista() {
        It = fin = inicio = nullptr;
    }
	int size() {return len;}
    Nodo<Tipo>* It;              
    void insertar(Tipo e) {      
        Nodo<Tipo>* n = new Nodo<Tipo>(e);
        if (inicio == nullptr)
            It = inicio = fin = n;
        else {
            fin->siguiente = n;
            fin = n;
        }
		len++;
    }
	void ejecutar(function<void(Tipo)> func) {
        Nodo<Tipo>* aux = inicio;
        while (aux->siguiente != nullptr) {
			func(aux->elemento);
            aux = aux->siguiente;
        }
		func(aux->elemento);
	}
    void mostrar(const function<void(Tipo)>& criterio = [](Tipo e){ 
															std::cout << e << "\n"; 
														} ) {
        Nodo<Tipo>* aux = inicio;
        while (aux->siguiente != nullptr) {
            criterio(aux->elemento); cout << " ";
            aux = aux->siguiente;
        }
        criterio(aux->elemento); cout << " ";
    }          

    void mostrar_short(const function<void(Tipo)>& criterio) {
		// 2 primeros y 2 ultimos
        Nodo<Tipo>* aux = inicio;
        for (int i = 0; i < len && aux; i++) {
			if (i < 2 || i >= len-3) {
				criterio(aux->elemento); cout << " ";
			}
			else if (i == 2) {
				cout << "...";
			}
            aux = aux->siguiente;
        }
    }          

    void iterar() { if (It->siguiente != nullptr) It = It->siguiente; else It = inicio; }
    void resetit() { It = inicio; }         
    Tipo getIt() { return It->elemento; }   
    Tipo getFin() { return fin->elemento; } 
	
	void quick_sort(const function<bool(Tipo, Tipo)>& f = [](Tipo a, Tipo b){ return a > b; }) {
		_quick_sort(inicio, fin, f);
	}
private:
	Nodo<Tipo>* parition(Nodo<Tipo> *first, Nodo<Tipo> *last, const function<bool(Tipo, Tipo)>& f)
	{
		//Get first node of given linked list
		Nodo<Tipo> *pivot = first;
		Nodo<Tipo> *front = first;
		Tipo temp;
		while (front != nullptr && front != last)
		{
			if (f(front->elemento, last->elemento))
			{
				pivot = first;
				//Swap node elemento
				temp = first->elemento;
				first->elemento = front->elemento;
				front->elemento = temp;
				//Visit to next node
				first = first->siguiente;
			}
			//Visit to next node
			front = front->siguiente;
		}
		//Change last node elemento to current node
		temp = first->elemento;
		first->elemento = last->elemento;
		last->elemento = temp;
		return pivot;
	}
	void _quick_sort(Nodo<Tipo>* first, Nodo<Tipo>* last, const function<bool(Tipo, Tipo)>& f) {
		if (first == last)
		{
			return;
		}
		Nodo<Tipo> *pivot = parition(first, last, f);
		if (pivot != NULL && pivot->siguiente != NULL)
		{
			_quick_sort(pivot->siguiente, last, f);
		}
		if (pivot != NULL && first != pivot)
		{
			_quick_sort(first, pivot, f);
		}
	}
};
