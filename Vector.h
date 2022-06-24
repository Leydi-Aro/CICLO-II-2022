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
        capacidad = 9;
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

    // aceder a valor por posicion
    T pos(int pos)
    {
        return arr[pos];
    }

    /*  void mostrar()
    {
        for (size_t i = 0; i < size; ++i)
        {
            cout << (arr[i]) << " ";
        }
    }*/

    void ver(function<void(T)> c)
    {
        for (size_t i = 0; i < size; ++i)
        {
            c(arr[i]);
        }
    }

    void fisher_yates()
    {
        for (int i = size - 1; i > 0; i--)
        {
            int j = (rand() % (i + 1));
            swap(&arr[j], &arr[i]);
        }
    }

    void OrdenamientoBurbuja(function<bool(T, T)> c)
    {
        for (size_t i = 0; i < size - 1; ++i)
        {
            for (size_t j = 0; j < size - 1 - i; ++j)
            {
                if (c(arr[j], arr[j + 1]))
                    swap(&arr[j], &arr[j + 1]);
            }
        }
    }

    void OrdenamientoIntercambio(function<bool(T, T)> c)
    {
        for (size_t i = 0; i < size - 1; i++)
        {
            for (size_t j = i + 1; j < size; j++)
            {
                if (c(arr[i], arr[j]))
                {
                    swap(&arr[i], &arr[j]);
                }
            }
        }
    }

    void Merge(function<bool(T, T)> c)
    {
        T *aux = new T[size];
        int i = 0;
        int j = size / 2;
        int k = 0;
        while (i < size / 2 && j < size)
        {
            if (c(arr[i], arr[j]))
            {
                aux[k] = arr[i];
                i++;
            }
            else
            {
                aux[k] = arr[j];
                j++;
            }
            k++;
        }
        while (i < size / 2)
        {
            aux[k] = arr[i];
            i++;
            k++;
        }
        while (j < size)
        {
            aux[k] = arr[j];
            j++;
            k++;
        }
        for (size_t i = 0; i < size; i++)
        {
            arr[i] = aux[i];
        }
        delete aux;
    }

    void MergeSort(function<bool(T, T)> c)
    {
        if (size > 1)
        {
            Vector<T> *a = new Vector<T>();
            Vector<T> *b = new Vector<T>();
            for (size_t i = 0; i < size; i++)
            {
                if (i < size / 2)
                    a->pushback(arr[i]);
                else
                    b->pushback(arr[i]);
            }
            a->MergeSort(c);
            b->MergeSort(c);
            Merge(c);
            delete a;
            delete b;
        }
    }
};
