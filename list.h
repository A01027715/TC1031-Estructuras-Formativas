#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>

template <class T> class List;
template <class T> class ListIterator;

using namespace std;

template <class T>
class Link {
private:
	Link(T val) : value(val), next(nullptr) {};

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
class List {
public:
	List();

	void     insertion(T);
	int      search(T);
	void     update(T, int);
	void     deleteAt(T);
	string   toString() const;

private:
	Link<T>  *head;
	int 	 size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
void List<T>::insertion(T valor) {
	Link<T>* newVal = new Link<T>(valor);

    if (head == nullptr) {
        head = newVal;
    }

	else {
        Link<T>* curr = head;
        while (curr -> next != nullptr) {
            curr = curr -> next;
        }
        curr -> next = newVal;
    }
}

template <class T>
int List<T>::search(T valor) {
	Link<T> *curr = head;
	int index = 0;

	while (curr) {
		if (curr -> value == valor) {
			return index;
		}

		curr = curr -> next;
		index++;
	}
	return -1;
}

template <class T>
void List<T>::update(T index, int valor) {
	Link<T> *curr = head;
	int currI = 0;

	while (curr) {
		if (currI == index) {
			curr -> value = valor;
			return;
		}

		curr = curr -> next;
		currI++;
	}
}

template <class T>
void List<T>::deleteAt(T index) {
	if (index == 0) {
		Link<T> *temp = head;
		head = head -> next;
		delete temp;
	}

	else {
		Link<T> *curr = head;
		int currI = 0;
		while (curr) {
			if (currI == index - 1) {
				Link<T> *temp = curr -> next;
				curr->next = temp -> next;
				delete temp;
				return;
			}

			curr = curr -> next;
			currI++;
		}
	}
}

template <class T>
string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p -> next != 0) {
			aux << ", ";
		}
		p = p -> next;
	}
	aux << "]";
	return aux.str();
}
#endif