#ifndef PIEZA_H
#define PIEZA_H

#include <SFML/Graphics.hpp>
#include "Constantes.h"

enum TipoPieza {
    I = 0,
    O = 1,
    T = 2,
    S = 3,
    Z = 4,
    J = 5,
    L = 6,
    NINGUNA = 7
};

extern const int FORMAS[7][4][4][4];

class Pieza {
	private:
	TipoPieza tipo;
	int rotacion;
	int x;
	int y;

public:
    Pieza();
    Pieza(TipoPieza t);
    Pieza(TipoPieza t, int rot, int px, int py);

    TipoPieza getTipo();
    int getRotacion();
    int getX();
    int getY();
    sf::Color getColor();
    static sf::Color getColorPorTipo(TipoPieza t);

    void setPosicion(int px, int py);
    void mover(int dx, int dy);
    void setRotacion(int r);
    void rotarHorario();
    void rotarAntiHorario();

    void getMatriz(int out[4][4]);
    void getMatrizRot(int rot, int out[4][4]);

    bool esVacia();
};

#endif

