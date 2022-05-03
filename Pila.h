#pragma once
#include <iostream>

template <typename T>
class Pila {

	template <typename G=T>
	struct Nodo {
		Nodo<G>* below;
		G value;
		Nodo(const G& elem) : value(elem) { 
			below = nullptr; 
		}
	};

    Nodo<T>* top;
    int tamanio;
public:
    Pila() {
        top = nullptr;
        tamanio = 0;
    }
    int Size() {
        return tamanio;
    }

    // O(1)
    void agregar(const T& elem) {
		if (!top) top = new Nodo<T>(elem);
		else {
			Nodo<T>* aux = new Nodo<T>(elem);
			aux->below = top;
			top = aux;
		}
		tamanio += 1;
    }
	
    //O(1)
    T popear() {
		if(!top) {
			std::cerr << "[-] Error al popear pila.";
		}
		T copy = top->value;
		Nodo<T>* aux = top->below;
		delete top;
		top = aux;
		tamanio--;
		return copy;
    }

    // O(1)
    T& arriba() {
		return top->value;
    }

    // O(n) - casos especiales
	void map(void(*f)(T)) {
		Nodo<T>* aux = top;
		while(aux) {
			f(aux->value);
			aux = aux->below;
		}
    }
};
