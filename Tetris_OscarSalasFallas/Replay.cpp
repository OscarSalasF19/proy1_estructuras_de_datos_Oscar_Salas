#include "Replay.h"
Replay::Replay(){
	this->actual = nullptr;
	this->cabeza = nullptr;
	this->cola = nullptr;
	this->tam = 0;
}
void Replay::agregarEstado(EstadoJuego* e){
	Nodo* nuevo = new Nodo;
	nuevo->estado.setTablero(e->getTablero());
	nuevo->estado.setPiezaActual(e->getPiezaActual());
	nuevo->estado.setSiguientePieza(e->getSiguientePieza());
	nuevo->estado.setBolsaActual(e->getBolsaActual());
	nuevo->estado.setHold(e->getHold());
	nuevo->estado.setLineas(e->getLineas());
	nuevo->estado.setNivel(e->getNivel());
	nuevo->estado.setPuntaje(e->getPuntaje());
	nuevo->siguiente = nullptr;
	nuevo ->anterior = nullptr;
	if(cabeza == nullptr && cola == nullptr && actual == nullptr){
		cabeza = nuevo;
		cola = nuevo;
		actual = nuevo;
		tam++;
		return;
	}
	if(actual->siguiente){
		eliminarEstados(actual);
	}
	actual->siguiente = nuevo;
	nuevo->anterior = actual;
	cola = nuevo;
	actual = nuevo;
	tam++;
}
void Replay::deshacer(){
	if(puedeDeshacer()){
		actual = actual->anterior;
	}
}
void Replay::rehacer(){
	if(puedeRehacer()){
		actual = actual->siguiente;
	}
}
void Replay::reiniciar(){
	while(cabeza){
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
		tam--;
	}
	cabeza = nullptr;
	cola = nullptr;
	actual = nullptr;
	EstadoJuego* nuevo = new EstadoJuego();
	agregarEstado(nuevo);
	delete nuevo;
}
Replay::~Replay(){
	while(cabeza){
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
		tam--;
	}
}

void Replay::reproducirDesdeInicio(){
	irAlInicio();
}

void Replay::irAlInicio(){
	actual = cabeza;
}

void Replay::irAlFinal(){
	actual = cola;
}

int Replay::getIndiceActual(){
	if(!actual || !cabeza){
		return 0;
	}
	int idx = 1;
	Nodo* aux = cabeza;
	while(aux && aux != actual){
		idx++;
		aux = aux->siguiente;
	}
	return idx;
}

void Replay::vaciar(){
	while(cabeza){
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
	}
	cabeza = nullptr;
	cola = nullptr;
	actual = nullptr;
	tam = 0;
}

void Replay::transferirDesde(Replay& origen){
	vaciar();
	this->cabeza = origen.cabeza;
	this->cola = origen.cola;
	this->actual = origen.actual;
	this->tam = origen.tam;
	origen.cabeza = nullptr;
	origen.cola = nullptr;
	origen.actual = nullptr;
	origen.tam = 0;
}
int Replay::getTam(){
	return tam;
}
bool Replay::puedeDeshacer(){
	if(actual && actual->anterior){
		return true;
	}
	return false;
}
bool Replay::puedeRehacer(){
	if(actual && actual->siguiente){
		return true;
	}
	return false;
}

EstadoJuego* Replay::getEstadoActual(){
	if(actual){
		return &(actual->estado);
	}
	return nullptr;
}

void Replay::eliminarEstados(Nodo* limite){
	Nodo* aux = cola;
	while(aux != limite){
		cola = cola->anterior;
		cola->siguiente = nullptr;
		delete aux;
		aux = cola;
		tam--;
	}
}

