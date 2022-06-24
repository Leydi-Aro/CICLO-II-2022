#pragma once
#include <iostream>
#include "Lambda.h"
#include <string>
#include <functional>
#include <fstream>
using namespace std;

template <class T>
class Nodo2 {
public:
	T elemento;
	Nodo2* izq;
	Nodo2* der;
	Nodo2(T elemento) {
		this->elemento = elemento;
		izq = der = nullptr;

	}

	Nodo2() {  }

};

template <class T>
class ArbolB {
	Nodo2<T>* raiz;

private:
	bool _insertar(Nodo2<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo2<T>(e);
			//nodo->elemento = e;
		}
		else if (e < nodo->elemento) {
			return _insertar(nodo->izq, e);
		}
		else if (e >= nodo->elemento) {
			return _insertar(nodo->der, e);
		}
	}
	//---------------------------------------------------------------------------------------
	void _enOrden(Nodo2<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		cout << nodo->elemento << " ";
		_enOrden(nodo->der);
	}

	void _preOrden(Nodo2<T>* nodo) {
		if (nodo == nullptr) return;
		cout << nodo->elemento << " ";
		_preOrden(nodo->izq);
		_preOrden(nodo->der);

	}
	void _postOrden(Nodo2<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		cout << nodo->elemento << " ";
	}

	//----------------------------------------------------------------------------------------
	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo2<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha
		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
public:
	ArbolB() {

		raiz = nullptr;
	}
	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
};