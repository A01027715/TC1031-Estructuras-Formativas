#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <sstream>

using namespace std;

template <typename T>

class DList {
private:
    struct Link {
        T data;
        Link* next;
        Link* prev;

        Link(T value) : data(value), next(0), prev(0) {}
    };

    Link* head;
    Link* tail;

public:
    DList() : head(nullptr), tail(nullptr) {}
    void insertion(T);
    T search(T value);
    void update(T index, int value);
    void deleteAt(int index);
    std::string toStringForward() const;
    std::string toStringBackward() const;
};


template <class T>
void DList<T>::insertion(T valor) {
	Link* newVal = new Link(valor);

    if (head == nullptr) {
        head = newVal;
		tail = newVal;
    }

	else {
		newVal -> prev = tail;
        tail -> next = newVal;
		tail= newVal;
    }
}

template <class T>
T DList<T>::search(T valor) {
	Link* curr = head;
	int pos = 0;

	while(curr){
		if (curr->data == valor){
			return pos;
		}
		curr = curr->next;
		pos++;
	}
	return -1;
}

template <class T>
void DList<T>::update(T index, int valor) {
	int pos = 0;
	Link* curr = head;
	while(curr){
		if (pos == index){
			curr->data = valor;
			break;
		}
		curr = curr->next;
		pos++;
	}
}

template <class T>
void DList<T>::deleteAt(int index) {
	if(index == 0){
		Link* pue = head;
		head = head->next;
		if (head){
			head->prev =nullptr;
		}else{
			tail = nullptr;
		}
		delete pue;
		return;
	};
	int pos = 0;
	Link* curr = head;
	while (curr){
		if (pos == index){
			if (curr->next){
				curr->next->prev = curr->prev;
			}
			if (curr->prev){
				curr->prev->next = curr->next;
			}
			if (curr==tail){
				tail = curr->prev;
			}
			delete curr;
			break;
		}
		curr = curr->next;
		pos++;
	}
}

template <class T>
string DList<T>::toStringForward() const {
	std::stringstream p;
	p << "[";
	Link* curr = head;
	while (curr) {
		p << curr->data;
		if (curr->next) {
			p << ", ";
		}
		curr = curr->next;
	}
	p << "]";
	return p.str();
}

template <class T>
string DList<T>::toStringBackward() const {
	std::stringstream p;
	p << "[";
	Link* curr = tail;
	while (curr) {
		p << curr->data;
		if (curr->prev) {
			p << ", ";
		}
		curr = curr->prev;
	}
	p << "]";
	return p.str();
}

#endif