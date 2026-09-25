#ifndef COLAPIEZAS_H
#define COLAPIEZAS_H
#include "Pieza.h"
#include <vector>
#include <cstdlib>
#include <ctime>
class ColaPiezas {
private:
	struct Nodo{
		TipoPieza dato;
		Nodo* siguiente;
	};
	Nodo* frente;
	Nodo* final;
	int tam;
public:
	ColaPiezas();
	void encolar(TipoPieza p);
	TipoPieza desencolar();
	TipoPieza getFrente();
	bool vacia();
	int getTam();
	TipoPieza* proximas3();
	void rellenarBolsa();
	~ColaPiezas();

};

#endif

