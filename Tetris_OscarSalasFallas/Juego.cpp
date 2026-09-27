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
	this->win = false;
	this->holdHecho = false;
	this->cantLineasPorLimpiar = 0;
	this->bomba = false;
	this->doblePuntos = false;
	this->caidaRapida = false;
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
	cantLineasPorLimpiar = 0;
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
	fijarPieza();
	agregarHistorial();
}
void Juego::fijarPieza(){
	tablero.insertaPieza(actual);
	if(bomba){
		int matrizActual[4][4];
		actual->getMatriz(matrizActual);
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j ++){
				if(matrizActual[i][j]== 1){
					tablero.eliminarFila(i + actual->getY());
					puntaje += 200*nivel;
					lineas ++;
					if(lineas >= LINEAS_POR_NIVEL * nivel){
						win = true;
					}
					j = 4;
				}
			}
		}
		bomba = false;
	}
	holdHecho = false;

	cantLineasPorLimpiar = 0;
	for(int i = 0; i < FILAS; i++){
		if(tablero.esFilaCompleta(i) && cantLineasPorLimpiar < 4){
			lineasPorLimpiar[cantLineasPorLimpiar] = i;
			cantLineasPorLimpiar++;
		}
	}

	if(cantLineasPorLimpiar == 0){
		spawnPieza();
	}
}
void Juego::verificarLineas(){
	int cantidadLineas = tablero.limpiarLineasCompletas(); 
	lineas += cantidadLineas;
	if(doblePuntos){
		puntaje += cantidadLineas * 200 * nivel * 2;
	}else{
		puntaje += cantidadLineas * 200 * nivel;	
	}
	if(lineas >= (LINEAS_POR_NIVEL * nivel)){
		win = true;
	}
}
void Juego::completarLimpiezaLineas(){
	verificarLineas();
	cantLineasPorLimpiar = 0;
	spawnPieza();
}
int Juego::getCantLineasPorLimpiar(){
	return cantLineasPorLimpiar;
}
int Juego::getLineaPorLimpiar(int idx){
	if(idx >= 0 && idx < cantLineasPorLimpiar){
		return lineasPorLimpiar[idx];
	}
	return -1;
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
	EstadoJuego* nuevoEstado = new EstadoJuego(tablero, actual, siguiente, cola, hold.top(), puntaje, lineas, nivel);
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
			Pieza sig = e->getSiguientePieza();
			siguiente = new Pieza(sig.getTipo(), sig.getRotacion(), sig.getX(), sig.getY());
			cola.copiarDesde(e->getBolsaActual());
			while(!hold.vacia()){
				hold.pop();
			}
			if(e->getHold() != NINGUNA){
				hold.push(e->getHold());
			}
			puntaje = e->getPuntaje();
			lineas = e->getLineas();
			nivel = e->getNivel();
			cantLineasPorLimpiar = 0;
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
			Pieza sig = e->getSiguientePieza();
			siguiente = new Pieza(sig.getTipo(), sig.getRotacion(), sig.getX(), sig.getY());
			cola.copiarDesde(e->getBolsaActual());
			while(!hold.vacia()){
				hold.pop();
			}
			if(e->getHold() != NINGUNA){
				hold.push(e->getHold());
			}
			puntaje = e->getPuntaje();
			lineas = e->getLineas();
			nivel = e->getNivel();
			cantLineasPorLimpiar = 0;
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
	if(caidaRapida){
		return tiempoCaida / 2.0;
	}
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

void Juego::actualizarEvento(int tiempoActual){
	if(eventos.vacia()){
		eventos.rellenar(tiempoActual);
	}
	if((caidaRapida || doblePuntos) && tiempoActual - eventoActual.momentoActivacion >= eventoActual.duracionSegundos){
		this->caidaRapida = false;
		this->doblePuntos = false;
	}
	if(eventos.debeDispararse(tiempoActual)){
		eventos.disparar(eventoActual);
		if(eventoActual.tipo == EV_AUMENTO_VELOCIDAD){
			this->caidaRapida = true;
		}
		else if(eventoActual.tipo == EV_BONUS_PUNTAJE){
			this->doblePuntos = true;
		}
		else{
			this->bomba = true;
		}
		eventoActual.momentoActivacion = tiempoActual;
	}

}

string Juego::proximoEvento(){
	Evento proximoE;
	if(eventos.proximo(proximoE)){
		return proximoE.descripcion;
	}
	return "Ninguno";
}
bool Juego::getCaidaRapida(){
	return caidaRapida;
}
bool Juego::getBomba(){
	return bomba;
}
bool Juego::getDoblePuntos(){
	return doblePuntos;
}

int Juego::duracionParaProximoEvento(int tiempoActual){
	Evento proximoE;
	if(eventos.proximo(proximoE)){
		int restante = proximoE.momentoDisparo - tiempoActual;
		return restante > 0 ? restante : 0;
	}
	return 0;
}

