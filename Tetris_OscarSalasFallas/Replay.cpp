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
	nuevo->estado.setHold(e->getHold());
	nuevo->estado.setLineas(e->getLineas());
	nuevo->estado.setNivel(e->getNivel());
	nuevo->estado.setPuntaje(e->getPuntaje());
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
}
Replay::~Replay(){
	while(cabeza){
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
	}
}

void Replay::reproducirDesdeInicio(){
	// TODO T3.2 SFML: recorrer cabeza->cola con sf::Clock 300-500ms y dibujar cada EstadoJuego via InterfazSFML
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

