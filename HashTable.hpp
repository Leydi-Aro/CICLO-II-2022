#include "Lista.h"
#include <functional>
using namespace std;

template<typename T>
class HashTable {
	Lista<T>* data;
	function<int(T)> hash_function;
	int size;
public:
	HashTable(int size=5) {
		this->size = size;
		data = new Lista<T>[size];
	}
	void add(const T& obj) {
		int pos = this->hash_function(obj) % size;
		data[pos].insertar(obj);
	}
	void set_hash_funcion(function<int(T)> hash_function) {
		this->hash_function = hash_function;
	}
	int Size() {
		int len = 0;
		for(int i =0; i < size; i++) {
			len += data[i].size();
		}
		return len;
	}

	void display(function<void(T)> f) {
		int total = 0;
		for(int i = 0; i < size; i++) {
			cout << "[" << i+1 << "] : {";
			data[i].mostrar_short(f);
			cout << "} Total: " << data[i].size() << "\n";
			total += data[i].size();
		}
		cout << "\nSe distribuyeron " << total << " datos en " << size << " listas\n";
	}
};
