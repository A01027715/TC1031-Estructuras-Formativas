/*
 * funciones.h
 *
 *  Created on: 24/08/2022
 *      Author: Ulises Orlando Carrizalez Lerín
 */

#ifndef Funcione_H_
#define Funcione_H_

#include <iostream>
#include <string>

using namespace std;

class Funciones {
public:
    int sumaIterativa(int n);
    int sumaRecursiva(int n);
    int sumaDirecta (int n); 
};

int Funciones :: sumaIterativa(int n) {
    int sum = 0;
	while (n != 0){
        sum = sum + n;
        n = n - 1;
    }
	return sum;
}

int Funciones :: sumaRecursiva(int n) {
	if (n == 0){return 0;}
	else {return n + sumaRecursiva(n-1);}
}

int Funciones :: sumaDirecta(int n) {
    return (n*(1 + n) / 2);
}
#endif