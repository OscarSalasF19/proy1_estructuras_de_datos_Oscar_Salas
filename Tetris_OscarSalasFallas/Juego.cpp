#include "Juego.h"

Juego::Juego(){
	this->tablero = Tablero();
	this->cola = ColaPiezas();
	this->hold = PilaHold();
	this->eventos = ColaEventos();
	this->actual = nullptr;
	this->siguiente = nullptr;
	this->puntaje = 0;
	this->lineas = 0;
	this->nivel = 1;
	this->gameOver = false;
	this->historial = Replay();
	this->tiempoCaida = TIEMPO_CAIDA_INICIAL_MS - nivel * 80;
	if(tiempoCaida < TIEMPO_CAIDA_MIN_MS){
		tiempoCaida = TIEMPO_CAIDA_MIN_MS;
	}
}
void Juego::iniciar(){
	tablero.crearTableroVacio();
	cola.rellenarBolsa();
	spawnPieza();
	historial.agregarEstado(new EstadoJuego(tablero,actual,hold.top(),puntaje, lineas, nivel));
	
}
void Juego::spawnPieza(){
	if(actual == nullptr && siguiente == nullptr){
	actual = new Pieza(cola.desencolar());
	siguiente = new Pieza(cola.desencolar());
	}
	else{
		delete actual;
		actual = siguiente;
		siguiente = new Pieza(cola.desencolar());
	}
	if(!tablero.puedeColocar(actual)){
		gameOver = true;
		return;
	}
	tablero.insertaPieza(actual);
}
void Juego::moverIzquierda(){
	tablero.limpiarPieza(actual);
	actual->mover(-1,0);
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
		return;
	}
	actual->mover(1,0);
	tablero.insertaPieza(actual);
}
void Juego::moverDerecha(){
	tablero.limpiarPieza(actual);
	actual->mover(1,0);
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
		return;
	}
	actual->mover(-1,0);
	tablero.insertaPieza(actual);
}
void Juego::rotarHorario(){
	tablero.limpiarPieza(actual);
	actual->rotarHorario();
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
		return;
	}
	actual->rotarAntiHorario();
	tablero.insertaPieza(actual);
}
void Juego::rotarAntiHorario(){
	tablero.limpiarPieza(actual);
	actual->rotarAntiHorario();
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
		return;
	}
	actual->rotarHorario();
	tablero.insertaPieza(actual);
}
void Juego::bajar(){
	tablero.limpiarPieza(actual);
	actual->mover(0,1);
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
		return;
	}
	actual->mover(0,-1);
	fijarPieza();
}
void Juego::hardDrop(){
	Pieza* aux = actual;
	while(tablero.puedeColocar(aux)){
		actual = aux;
		aux->mover(0,1);
	}
	tablero.insertaPieza(actual);
	holdHecho = false;
	int cant = tablero.limpiarLineasCompletas();
	lineas+= cant;
	puntaje += 200 * cant * nivel;
	spawnPieza();
}
void Juego::fijarPieza(){
	tablero.insertaPieza(actual);
	verificarLineas();
	spawnPieza();
	holdHecho = false;
}
void Juego::verificarLineas(){
	int cantidadLineas = tablero.limpiarLineasCompletas(); 
	lineas += cantidadLineas;
	puntaje += cantidadLineas * 200 * nivel;
}

void Juego::intercambiarHold(){
	if(!holdHecho){
	tablero.limpiarPieza(actual);
	if(hold.vacia()){
		hold.push(actual->getTipo());
		spawnPieza();
		holdHecho = true;
		return;
	}
	TipoPieza aux = hold.push(actual->getTipo());
	delete actual;
	actual = new Pieza(aux);
	tablero.insertaPieza(actual);
	}
}

void Juego::agregarHistorial(){
	EstadoJuego* nuevoEstado = new EstadoJuego(tablero, actual, hold.top(), puntaje, lineas, nivel);
	
}

