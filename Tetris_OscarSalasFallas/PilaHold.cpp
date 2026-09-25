#include "PilaHold.h"

PilaHold::PilaHold() {
	this->tope = nullptr;
}
TipoPieza PilaHold::push(TipoPieza p){
	Nodo* nuevo = new Nodo{p, nullptr};
	TipoPieza aux = NINGUNA;
	if(tope != nullptr){
		aux = tope->dato;
		delete tope;
	}
	tope = nuevo;
	return aux;
	
}
TipoPieza PilaHold::top(){
	if(tope != nullptr){
		return tope->dato;
	}
	return NINGUNA;
}

TipoPieza PilaHold::pop(){
	if(tope!= nullptr){
		TipoPieza aux = tope->dato;
		delete tope;
		tope = nullptr;
		return aux;
	}
	return NINGUNA;
}
bool PilaHold::vacia(){
	if(tope == nullptr){
		return true;
	}
	return false;
}

PilaHold::~PilaHold(){
	if(tope != nullptr){
		delete tope;
	}
}

