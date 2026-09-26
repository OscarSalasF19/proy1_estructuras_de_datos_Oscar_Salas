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
	bool win;
	
public:
	Juego();
	~Juego();
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
	void deshacer();
	void rehacer();

	Tablero& getTablero();
	ColaPiezas& getCola();
	PilaHold& getHold();
	Pieza* getActual();
	Pieza* getSiguiente();
	int getPuntaje();
	int getLineas();
	int getNivel();
	float getTiempoCaida();
	bool getGameOver();
	Replay& getHistorial();
	bool getHoldHecho();
	bool getWin();
	void setNivel(int nivel);
};
#endif

