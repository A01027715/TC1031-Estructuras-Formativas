#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

template <class T>
class Heap {
    private:
        T *data;
        int tamaño;
        int count;
        int parent(int);
        int left(int);
        int right(int);
        void heapify(int);
        void swap(int, int);

    public:
        Heap(int);
        void push(T);
        void pop();
        T top();
        bool empty();
        int size();
        string toString() const;

};

template <class T>
Heap<T>::Heap(int sze)  {
	tamaño = sze + 1;
	data = new T[tamaño];
	count = 0;
}

template <class T>
int Heap<T>::parent( int pos) {
	return (pos - 1) / 2;
}

template <class T>
int Heap<T>::left(int pos) {
	return ((2 * pos) + 1);
}

template <class T>
int Heap<T>::right(int pos) {
	return ((2 * pos) + 2);
}

template <class T>
void Heap<T>::swap(int i, int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(int pos) {
	int le = left(pos);
	int ri = right(pos);
	int min = pos;
	if (le <= count && data[le] < data[min]) {
		min = le;
	}
	if (ri <= count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::push(T val){
	int pos;
	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

template <class T>
void Heap<T>::pop(){
    data[0] = data[--count];
	heapify(0);
}

template <class T>
T Heap<T>::top(){
    if (empty()) {
		return -1;
	}
    T aux = data[0];
	return aux;
}

template <class T>
bool Heap<T>::empty(){
    return (count == 0);
}

template <class T>
int Heap<T>::size(){
if (empty()) {
	return -1;
}
 return count;
}

template <class T>
string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}