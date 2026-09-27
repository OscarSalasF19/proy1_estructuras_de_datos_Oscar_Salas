#include "EstadoJuego.h"

EstadoJuego::EstadoJuego(){
	tablero = Tablero();
	tablero.crearTableroVacio();
	this->hold = NINGUNA;
	this->piezaActual = NINGUNA;
	this->siguientePieza = NINGUNA;
	this->puntaje = 0;
	this->lineas = 0;
	this->nivel = 0;
}

EstadoJuego::EstadoJuego(Tablero& t, Pieza* p, Pieza* siguientePieza, ColaPiezas& bolsa, TipoPieza h, int& punt, int& lin, int& niv){
	this->tablero.copiarDesde(t);
	this->piezaActual = Pieza(p->getTipo());
	this->piezaActual.setPosicion(p->getX(), p->getY());
	this->piezaActual.setRotacion(p->getRotacion());
	this->siguientePieza = Pieza(siguientePieza->getTipo());
	this->siguientePieza.setPosicion(siguientePieza->getX(), siguientePieza->getY());
	this->siguientePieza.setRotacion(siguientePieza->getRotacion());
	this->bolsaActual.copiarDesde(bolsa);
	this->hold = h;
	this->puntaje = punt;
	this->lineas = lin;
	this->nivel = niv;
}

Tablero& EstadoJuego::getTablero(){
	return tablero;
}

void EstadoJuego::setTablero(Tablero& t){
	this->tablero.copiarDesde(t);
}

Pieza EstadoJuego::getPiezaActual(){
	return piezaActual;
}

void EstadoJuego::setPiezaActual(Pieza p){
	this->piezaActual = p;
}

Pieza EstadoJuego::getSiguientePieza(){
	return siguientePieza;
}

void EstadoJuego::setSiguientePieza(Pieza p){
	this->siguientePieza = p;
}

Pieza EstadoJuego::getSiguiente(){
	return siguientePieza;
}

void EstadoJuego::setSiguiente(Pieza p){
	this->siguientePieza = p;
}

ColaPiezas& EstadoJuego::getBolsaActual(){
	return bolsaActual;
}

void EstadoJuego::setBolsaActual(ColaPiezas& bolsa){
	this->bolsaActual.copiarDesde(bolsa);
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
