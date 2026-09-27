#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"

class EstadoJuego {
private:
	Tablero tablero;
	Pieza piezaActual;
	Pieza siguientePieza;
	ColaPiezas bolsaActual;
	TipoPieza hold;
	int puntaje;
	int lineas;
	int nivel;

public:
	EstadoJuego();
	EstadoJuego(Tablero& t, Pieza* p, Pieza* siguientePieza, ColaPiezas& bolsa, TipoPieza h, int& punt, int& lin, int& niv);

	Tablero& getTablero();
	void setTablero(Tablero& t);

	Pieza getPiezaActual();
	void setPiezaActual(Pieza p);

	Pieza getSiguientePieza();
	void setSiguientePieza(Pieza p);
	Pieza getSiguiente();
	void setSiguiente(Pieza p);

	ColaPiezas& getBolsaActual();
	void setBolsaActual(ColaPiezas& bolsa);

	TipoPieza getHold();
	void setHold(TipoPieza h);

	int getPuntaje();
	void setPuntaje(int p);

	int getLineas();
	void setLineas(int l);

	int getNivel();
	void setNivel(int n);
};

#endif
