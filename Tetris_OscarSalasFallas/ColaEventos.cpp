#include "ColaEventos.h"

ColaEventos::ColaEventos(){
	this->cabeza = nullptr;
	this->tam = 0;
}

ColaEventos::~ColaEventos(){
	while(cabeza){
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
	}
}
	
void ColaEventos::programar(Evento e){
	Nodo* nuevo = new Nodo{e, nullptr};
	if(cabeza == nullptr){
		cabeza = nuevo;
		tam++;
		return;
	}
	if(cabeza->dato.momentoDisparo > e.momentoDisparo){
		nuevo->siguiente = cabeza;
		cabeza = nuevo;
		tam++;
		return;
	}
	Nodo* aux = cabeza;
	while(aux->siguiente && aux->siguiente->dato.momentoDisparo <= e.momentoDisparo){
		aux = aux->siguiente;
	}
	nuevo->siguiente = aux->siguiente;
	aux->siguiente = nuevo;
	tam++;
}
	
bool ColaEventos::proximo(Evento& eSalida){
	if(cabeza){
		eSalida = cabeza->dato;
		return true;
	}
	return false;
	
}
	
bool ColaEventos::debeDispararse(int tiempoActual){
	if(cabeza && cabeza->dato.momentoDisparo <= tiempoActual){
		return true;
	}
	return false;
}
	
bool ColaEventos::disparar(Evento& eSalida){
	if(cabeza){
		eSalida = cabeza->dato;
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		tam--;
		delete aux;
		return true;
	}
	return false;
}
	
bool ColaEventos::vacia(){
	if(!cabeza){
		return true;
	}
	return false;
}
	
	
	
void ColaEventos::rellenar(int tiempoActual){
	while(cabeza){
		Nodo* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
		tam--;
	}
	programar({EV_AUMENTO_VELOCIDAD, tiempoActual + 30, "Aumento velocidad", 0, 10});
	programar({EV_BONUS_PUNTAJE, tiempoActual + 80, "Puntos dobles", 0, 15});
	programar({EV_PIEZA_ESPECIAL, tiempoActual + 60, "Bomba",0,0});
	
}
