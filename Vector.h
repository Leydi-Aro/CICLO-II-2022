#pragma once
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template <typename T>
class Vector
{
public:
    T *arr;
    int size;
    int capacidad;

public:
    // Tipo pos;
    Vector()
    {
        capacidad = 2;
        size = 0;
        arr = new T[capacidad];
    };

    void autoincremento()
    {
        capacidad *= 1.2;
        T *aux = new T[capacidad];
        for (size_t i = 0; i < size; ++i)
            aux[i] = arr[i];
        delete arr;
        arr = aux;
    }

    void pushback(T elemento)
    {
        if (size == capacidad)
            autoincremento();
        if (size < capacidad)
            arr[size++] = elemento;
    }

    void swap(T *a, T *b)
    {
        T aux = *a;
        *a = *b;
        *b = aux;
    }

    //aceder a valor por posicion
    T pos(int pos){
        return arr[pos];
    }

    void mostrar()
    {
        for (size_t i = 0; i < size; ++i)
        {
            cout << (arr[i]) << " ";
        }
    }
};
