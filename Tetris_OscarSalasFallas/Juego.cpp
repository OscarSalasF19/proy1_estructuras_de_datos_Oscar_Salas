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
	setNivel(1);
	this->gameOver = false;
	this->historial = Replay();
	win = false;
	holdHecho = false;
}

Juego::~Juego(){
	if(actual){
		delete actual;
		actual = nullptr;
	}
	if(siguiente){
		delete siguiente;
		siguiente = nullptr;
	}
}
void Juego::iniciar(){
	tablero.crearTableroVacio();
	cola.rellenarBolsa();
	spawnPieza();
	
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
	agregarHistorial();
}
void Juego::moverIzquierda(){
	tablero.limpiarPieza(actual);
	actual->mover(-1,0);
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
	}else{
		actual->mover(1,0);
		tablero.insertaPieza(actual);	
	}
	agregarHistorial();
}
void Juego::moverDerecha(){
	tablero.limpiarPieza(actual);
	actual->mover(1,0);
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
	}else{
		actual->mover(-1,0);
		tablero.insertaPieza(actual);	
	}
	agregarHistorial();
}
void Juego::rotarHorario(){
	tablero.limpiarPieza(actual);
	actual->rotarHorario();
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
	}
	else{
		actual->rotarAntiHorario();
		tablero.insertaPieza(actual);	
	}
	agregarHistorial();
}
void Juego::rotarAntiHorario(){
	tablero.limpiarPieza(actual);
	actual->rotarAntiHorario();
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
	}
	else{
		actual->rotarHorario();
		tablero.insertaPieza(actual);
	}
	agregarHistorial();
}
void Juego::bajar(){
	tablero.limpiarPieza(actual);
	actual->mover(0,1);
	if(tablero.puedeColocar(actual)){
		tablero.insertaPieza(actual);
		return;
	}else{
		actual->mover(0,-1);
		fijarPieza();	
	}
	agregarHistorial();
	
}
void Juego::hardDrop(){
	tablero.limpiarPieza(actual);
	Pieza aux = *actual;
	while(tablero.puedeColocar(&aux)){
		*actual = aux;
		aux.mover(0,1);
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
	if(lineas >= (LINEAS_POR_NIVEL * nivel)){
		win = true;
	}
}

void Juego::intercambiarHold(){
	if(!holdHecho){
	tablero.limpiarPieza(actual);
	if(hold.vacia()){
		hold.push(actual->getTipo());
		spawnPieza();
		holdHecho = true;
		agregarHistorial();
		return;
	}
	TipoPieza aux = hold.push(actual->getTipo());
	delete actual;
	actual = new Pieza(aux);
	tablero.insertaPieza(actual);
	agregarHistorial();
	holdHecho = true;
	}
}

void Juego::agregarHistorial(){
	EstadoJuego* nuevoEstado = new EstadoJuego(tablero, actual, hold.top(), puntaje, lineas, nivel);
	historial.agregarEstado(nuevoEstado);
	delete nuevoEstado;
	
}

void Juego::deshacer(){
	if(historial.puedeDeshacer()){
		historial.deshacer();
		EstadoJuego* e = historial.getEstadoActual();
		if(e){
			tablero.copiarDesde(e->getTablero());
			if(actual){
				delete actual;
			}
			Pieza p = e->getPiezaActual();
			actual = new Pieza(p.getTipo(), p.getRotacion(), p.getX(), p.getY());
			while(!hold.vacia()){
				hold.pop();
			}
			if(e->getHold() != NINGUNA){
				hold.push(e->getHold());
			}
			puntaje = e->getPuntaje();
			lineas = e->getLineas();
			nivel = e->getNivel();
		}
	}
}

void Juego::rehacer(){
	if(historial.puedeRehacer()){
		historial.rehacer();
		EstadoJuego* e = historial.getEstadoActual();
		if(e){
			tablero.copiarDesde(e->getTablero());
			if(actual){
				delete actual;
			}
			Pieza p = e->getPiezaActual();
			actual = new Pieza(p.getTipo(), p.getRotacion(), p.getX(), p.getY());
			while(!hold.vacia()){
				hold.pop();
			}
			if(e->getHold() != NINGUNA){
				hold.push(e->getHold());
			}
			puntaje = e->getPuntaje();
			lineas = e->getLineas();
			nivel = e->getNivel();
		}
	}
}

Tablero& Juego::getTablero(){ 
	return tablero; 
}
ColaPiezas& Juego::getCola(){ 
	return cola; 
}
PilaHold& Juego::getHold(){ 
	return hold; 
}
Pieza* Juego::getActual(){ 
	return actual; 
}
Pieza* Juego::getSiguiente(){ 
	return siguiente; 
}
int Juego::getPuntaje(){ 
	return puntaje; 
}
int Juego::getLineas(){ 
	return lineas; 
}
int Juego::getNivel(){ 
	return nivel; 
}
float Juego::getTiempoCaida(){ 
	return tiempoCaida; 
}
bool Juego::getGameOver(){ 
	return gameOver; 
}
Replay& Juego::getHistorial(){ 
	return historial; 
}
bool Juego::getHoldHecho(){ 
	return holdHecho; 
}
bool Juego::getWin(){ 
	return win; 
}
void Juego::setNivel(int nivel){
	this->nivel = nivel;
	this->tiempoCaida = TIEMPO_CAIDA_INICIAL_MS - this->nivel * DECREMENTO_POR_NIVEL_MS;
	if(tiempoCaida < TIEMPO_CAIDA_MIN_MS){
		tiempoCaida = TIEMPO_CAIDA_MIN_MS;
	}
	
}

