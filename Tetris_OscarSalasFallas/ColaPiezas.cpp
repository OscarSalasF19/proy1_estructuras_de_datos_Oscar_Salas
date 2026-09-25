#include "ColaPiezas.h"

ColaPiezas::ColaPiezas() {
	this->frente = nullptr;
	this->final = nullptr;
	this->tam = 0;
}

void ColaPiezas::encolar(TipoPieza p){
	Nodo* nuevo = new Nodo{p, nullptr};
	if(this->frente == nullptr && final == nullptr){
		frente = nuevo;
		final = nuevo;
		tam++;
		return;
	}
	final->siguiente = nuevo;
	final = nuevo;
	tam++;
}
TipoPieza ColaPiezas::desencolar(){
	TipoPieza auxP = frente->dato;
	Nodo* aux = frente;
	frente = frente->siguiente;
	if(frente == nullptr){
		final = nullptr;
	}
	tam--;
	delete aux;
	if(vacia()){
		rellenarBolsa();
	}
	return auxP;
}
TipoPieza ColaPiezas::getFrente(){
	if(frente == nullptr){
		return 	NINGUNA;
	}
	return frente->dato;
}
bool ColaPiezas::vacia(){
	if(tam == 0){
		return true;
	}
	return false;
}
int ColaPiezas::getTam(){
	return tam;
}
TipoPieza* ColaPiezas::proximas3(){
	TipoPieza* prox3 = new TipoPieza[3];
	int counter = 0;
	Nodo* aux = frente;
	while(counter < tam && counter < 3){
		prox3[counter] = aux->dato;
		aux = aux->siguiente;
		counter++;
	}
	for(int i = counter; i < 3; i++){
		prox3[i] = NINGUNA;
	}
	return prox3;
}

void ColaPiezas::rellenarBolsa(){
	std::vector<TipoPieza> piezas = {I,O,T,S,Z,J,L};
	while(!piezas.empty()){
		int idxPieza = rand() % piezas.size();
		encolar(piezas[idxPieza]);
		piezas.erase(piezas.begin() + idxPieza);
	}
}
ColaPiezas::~ColaPiezas(){
	while(frente){
		Nodo* aux = frente;
		frente = frente->siguiente;
		delete aux;
		if(frente == nullptr){
			final == nullptr;
		}
	}
}




