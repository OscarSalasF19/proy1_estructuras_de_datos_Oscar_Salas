#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H

#include "Tablero.h"
#include "Pieza.h"

class EstadoJuego {
private:
	Tablero tablero;
	Pieza piezaActual;
	TipoPieza hold;
	int puntaje;
	int lineas;
	int nivel;

public:
	EstadoJuego();
	EstadoJuego(Tablero t, Pieza p, TipoPieza h, int punt, int lin, int niv);

	Tablero getTablero();
	void setTablero(Tablero t);

	Pieza getPiezaActual();
	void setPiezaActual(Pieza p);

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
