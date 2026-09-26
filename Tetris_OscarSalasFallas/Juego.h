#ifndef JUEGO_H
#define JUEGO_H
#include "Tablero.h"
#include "PilaHold.h"
#include "ColaPiezas.h"
#include "ColaEventos.h"
#include "Pieza.h"
#include "Replay.h"
#include "Constantes.h"
class Juego {
private:
	Tablero tablero;
	ColaPiezas cola;
	PilaHold hold;
	ColaEventos eventos;
	Pieza* actual;
	Pieza* siguiente;
	int puntaje;
	int lineas;
	int nivel;
	float tiempoCaida;
	bool gameOver;
	Replay historial;
	bool holdHecho;
	
public:
	Juego();
	void iniciar();
	void spawnPieza();
	void moverIzquierda();
	void moverDerecha();
	void rotarHorario();
	void rotarAntiHorario();
	void bajar();
	void hardDrop();
	void fijarPieza();
	void verificarLineas();
	void intercambiarHold();
	void agregarHistorial();
	

};

#endif

