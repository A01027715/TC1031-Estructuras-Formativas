#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic {
private:
    struct Node {
        Key key;
        Value val;
        bool filled;

        Node() : filled(false) {}
    };
    Node* table;
    Key IV;
    int tam;
    unsigned int (*hasher)(const Key);

public:
    Quadratic(int, Key, unsigned int (*func)(const Key));
    void put(const Key&, const Value&);
    Value get(const Key&);
    string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value> :: Quadratic (int Tam, Key inicial, unsigned int (*hash)(const Key)){
    tam= Tam;
    table = new Node[tam];
    IV= inicial;
    hasher= hash;
}

template <class Key, class Value>
void Quadratic<Key, Value> :: put(const Key& key, const Value& val) {
    int index = hasher(key) % tam;
    int IndexO = index;
    int x = 1;

    while (table[index].filled) {
        index = (IndexO + x * x) % tam; 
        x++;
    }

    table[index].key = key;
    table[index].val = val;
    table[index].filled = true;
}

template <class Key, class Value>
Value Quadratic<Key, Value> :: get(const Key& key) {
    unsigned int index = hasher(key) % tam;
    unsigned int IndexO = index;
    int i = 1;

    while (table[index].filled) {
        if (table[index].key == key) {
            return table[index].val;
        }
        index = (IndexO + i * i) % tam; 
        i++;
    }

    throw runtime_error("LLAVE NO ENCONTRADA");
}

template <class Key, class Value>
string Quadratic<Key, Value> :: toString() const {
    stringstream aux;
    for (int i = 0; i < tam; i++) {
        if (table[i].filled) {
            aux << "(" << i << " " << table[i].key << " : " << table[i].val << ") ";
        }
    }
    return aux.str();
}

#endif