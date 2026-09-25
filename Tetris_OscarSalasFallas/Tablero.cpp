#include "Tablero.h"

Tablero::Tablero(){
	this->cabeza = nullptr;
}

void Tablero::copiarDesde(Tablero& origen){
	if(this->cabeza == nullptr){
		crearTableroVacio();
	}
	Fila* auxOrigen = origen.cabeza;
	Fila* auxDestino = this->cabeza;
	while(auxOrigen && auxDestino){
		for(int c=0; c<10; c++){
			auxDestino->celdas[c] = auxOrigen->celdas[c];
		}
		auxOrigen = auxOrigen->siguiente;
		auxDestino = auxDestino->siguiente;
	}
}

void Tablero::crearTableroVacio(){
	for(int i = 0; i < numFilas; i++){
		insertarFilaVaciaAlInicio();
	}
}
int Tablero::getCelda(int indice, int celda){
	Fila* aux = cabeza;
	if(indice < numFilas){
		for(int i = 0; i < indice; i++){
			aux = aux->siguiente;
		}
		if(celda < 10){
			return aux->celdas[celda];	
		}
		return -1;
	}
	return -1;
	
}
void Tablero::setCelda(int fila, int celda, int valor){
	Fila* aux = cabeza;
	if(fila < numFilas){
		for(int i = 0; i < fila; i++){
			aux = aux->siguiente;
		}
		if(celda < 10){
			aux->celdas[celda] = valor;	
		}
	}
}
bool Tablero::esFilaCompleta(int indice){
	if(indice >= numFilas){
		return false;
	}
	bool completa = true;
	Fila* aux = cabeza;
	for(int i = 0; i < indice; i ++){
		aux = aux->siguiente;
	}
	for(int i = 0; i< 10; i++){
		if(aux->celdas[i] == 0){
			completa = false;
		}
	}
	return completa;
}
bool Tablero::eliminarFila(int indice){
	if(indice >= numFilas){
		return false;
	}
	Fila* aux = cabeza;
	Fila* anterior = nullptr;
	if(indice == 0){
		cabeza = cabeza->siguiente;
		delete aux;
		return true;
	}
	for(int i = 0; i < indice; i ++){
		anterior = aux;
		aux = aux->siguiente;
	}
	
	anterior->siguiente = aux->siguiente;
	aux->siguiente = nullptr;
	delete aux;
	insertarFilaVaciaAlInicio();
	return true;
}
void Tablero::insertarFilaVaciaAlInicio(){
	Fila* nueva = new Fila();
	nueva->siguiente = nullptr;
	for(int i = 0; i < 10; i++){
		nueva->celdas[i] = 0;
	}
	if(cabeza == nullptr){
		cabeza = nueva;
		return;
	}
	nueva->siguiente = cabeza;
	cabeza = nueva;
}
void Tablero::limpiarLineasCompletas(){
	
	for(int i = 0; i < numFilas; i++){
		if(esFilaCompleta(i)){
			eliminarFila(i);
		}
	}
	
}
bool Tablero::estaOcupada(int fila, int celda){
	Fila* aux = cabeza;
	if(fila < numFilas){
		for(int i = 0; i < fila; i++){
			aux = aux->siguiente;
		}
		if(celda < 10){
			return aux->celdas[celda] == 1;	
		}
		return false;
	}
	return false;
	
}
void Tablero::imprimirConsola(){
	Fila* aux = cabeza;
	for(int i = 0; i < numFilas; i++){
		for(int j = 0; j < 10; j++){
			std::cout << aux->celdas[j] << " , ";
		}
		std::cout << "\n";
		aux = aux->siguiente;
	}
}
Tablero::~Tablero(){
	while(cabeza){
		Fila* aux = cabeza;
		cabeza = cabeza->siguiente;
		delete aux;
	}
}

