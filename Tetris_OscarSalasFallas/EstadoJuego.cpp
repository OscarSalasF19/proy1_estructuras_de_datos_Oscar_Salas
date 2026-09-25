#include "EstadoJuego.h"

EstadoJuego::EstadoJuego(){
	tablero = Tablero();
	tablero.crearTableroVacio();
	this->hold = NINGUNA;
	this->puntaje = 0;
	this->lineas = 0;
	this->nivel = 0;
}

EstadoJuego::EstadoJuego(Tablero t, Pieza p, TipoPieza h, int punt, int lin, int niv){
	this->tablero.copiarDesde(t);
	this->piezaActual = p;
	this->hold = h;
	this->puntaje = punt;
	this->lineas = lin;
	this->nivel = niv;
}

Tablero EstadoJuego::getTablero(){
	return tablero;
}

void EstadoJuego::setTablero(Tablero t){
	this->tablero.copiarDesde(t);
}

Pieza EstadoJuego::getPiezaActual(){
	return piezaActual;
}

void EstadoJuego::setPiezaActual(Pieza p){
	this->piezaActual = p;
}

TipoPieza EstadoJuego::getHold(){
	return hold;
}

void EstadoJuego::setHold(TipoPieza h){
	this->hold = h;
}

int EstadoJuego::getPuntaje(){
	return puntaje;
}

void EstadoJuego::setPuntaje(int p){
	this->puntaje = p;
}

int EstadoJuego::getLineas(){
	return lineas;
}

void EstadoJuego::setLineas(int l){
	this->lineas = l;
}

int EstadoJuego::getNivel(){
	return nivel;
}

void EstadoJuego::setNivel(int n){
	this->nivel = n;
}
