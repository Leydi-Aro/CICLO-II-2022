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
        T *aux = new T[size]; //--> 1 + 1 + 1 = 3
        int i = 0;            //--> 1 = 1
        int j = size / 2;      //--> 1 + 1 + 1 = 3
        int k = 0;             //--> 1 = 1

        while (i < size / 2 && j < size) //--> 1 + n(3 + interna)
        {   
            if (c(arr[i], arr[j])) //--> 1 + max(interna if, interna else)
            { 
                aux[k] = arr[i]; //--> 1 + 1 + 1 = 3
                i++; //--> 2 = 2
                //interna if = 3 + 2 = 5
            }
            else
            {
                aux[k] = arr[j]; //--> 1 + 1 + 1 = 3
                j++;          //--> 2 = 2
                //interna else = 3 + 2 = 5
            }
            k++; //--> 2 = 2
        }
        while (i < size / 2) //--> 1 +  n(2 + interna)
        {
            aux[k] = arr[i]; //--> 1 + 1 + 1 = 3
            i++; //--> 2 = 2
            k++; //--> 2 = 2
            //interna = 3 + 2 + 2 = 7 
        }
        while (j < size) //--> 1 + n(2 + interna)
        {
            aux[k] = arr[j]; //--> 1 + 1 + 1 = 3
            j++; //--> 2 = 2
            k++; //--> 2 = 2
            //interna = 3 + 2 + 2 = 7
        }
        for (size_t i = 0; i < size; i++) //1 + n(1 + interna + 2)
        {
            arr[i] = aux[i]; //--> 1 + 1 + 1 = 3
            //interna = 3
        }
        delete aux; //-->1
    }
    //BigO detallada: 3+1+3+1+1+n(3 + (1+ 5 +2))+1+n(2+7)+1 +n(2+7) + 1 +n(2+7) + 1 +n(1+3+2) +1 = 44n + 14
    //BigO: O(n)

    void MergeSort(function<bool(T, T)> c)
    {
        if (size > 1) //--> 1 +(interna)
        {
            Vector<T> *a = new Vector<T>(); //4
            Vector<T> *b = new Vector<T>(); //4
            for (size_t i = 0; i < size; i++) //1 + n(1 + interna +2)
            {
                if (i < size / 2) //--> 2 + max(interna if, interna else)
                    a->pushback(arr[i]); //3
                else
                    b->pushback(arr[i]); //3
            }
            a->MergeSort(c); // 1 + 2 = 3
            b->MergeSort(c); // 1 + 2 = 3
            Merge(c); //2
            delete a; //1
            delete b; //1
        }
    }
    //BigO detallada: 1 + (4+4+1+n(1+(2+3)+2))+3+3+2+1+1 = 8n + 20
    //BigO: O(n)
};
