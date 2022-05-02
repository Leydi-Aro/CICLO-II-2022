#include <iostream>
#include "Lista.h"

int main() {
	Lista<int> pito;
	pito.insertar(3);
	pito.insertar(5);
	pito.insertar(1);
	pito.insertar(3);
	pito.insertar(2);

	pito.mostrar();
	pito.quick_sort([](int a, int b){return a > b;});
	std::cout << "\n";
	pito.mostrar();
	std::cout << "\n";
	return 0;
}
