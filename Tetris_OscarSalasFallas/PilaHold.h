#ifndef PILAHOLD_H
#define PILAHOLD_H
#include "Pieza.h"

class PilaHold {
private:
	struct Nodo{
		TipoPieza dato;
		Nodo* siguiente;
	};
	Nodo* tope;
public:
	PilaHold();
	TipoPieza push(TipoPieza p);
	TipoPieza pop();
	TipoPieza top();
	bool vacia();
	~PilaHold();
};

#endif

