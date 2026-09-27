#include "Pieza.h"
const int FORMAS[7][4][4][4] = {
    {
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}
    },
    {
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
    },
    {
        {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    {
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}
    },
    {
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}
    },
    {
        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}, 
        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}} 
    },
    {
        {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}} 
    }
};

Pieza::Pieza(){
	this->tipo = NINGUNA;
	this->rotacion = 0;
	this->x = 3;
	this->y = 0;
}

Pieza::Pieza(TipoPieza t){
	this->tipo = t;
	this->rotacion = 0;
	this->x = 3;
	this->y = 0;
}

Pieza::Pieza(TipoPieza t, int rot, int px, int py){
	this->tipo = t;
	this->rotacion = rot % 4;
	this->x = px;
	this->y = py;
    if (rotacion < 0) rotacion += 4;
}

TipoPieza Pieza::getTipo(){ 
	return tipo; 
}
int Pieza::getRotacion(){ 
	return rotacion; 
}
int Pieza::getX(){ 
	return x; 
}
int Pieza::getY(){ 
	return y; 
}

bool Pieza::esVacia(){ 
	return tipo == NINGUNA; 
}

sf::Color Pieza::getColorPorTipo(TipoPieza t) {
    switch (t) {
        case I: return COLOR_I;
        case O: return COLOR_O;
        case T: return COLOR_T;
        case S: return COLOR_S;
        case Z: return COLOR_Z;
        case J: return COLOR_J;
        case L: return COLOR_L;
        default: return COLOR_VACIO;
    }
}

sf::Color Pieza::getColor(){
    return getColorPorTipo(tipo);
}

void Pieza::setPosicion(int px, int py){
	x = px; 
	y = py; 
}
void Pieza::mover(int dx, int dy){ 
	x += dx;
	y += dy; 
}
void Pieza::setRotacion(int r) {
    rotacion = r % 4;
    if (rotacion < 0) rotacion += 4;
}
void Pieza::rotarHorario() { 
	rotacion = (rotacion + 1) % 4; 
}
void Pieza::rotarAntiHorario() { 
	rotacion = (rotacion + 3) % 4; 
}


void Pieza::getMatriz(int out[4][4]){
    getMatrizRot(rotacion, out);
}

void Pieza::getMatrizRot(int rot, int out[4][4]){
    if (tipo == NINGUNA) {
        for (int r = 0; r < 4; r++)
            for (int c = 0; c < 4; c++) out[r][c] = 0;
        return;
    }
    int r = rot % 4;
    if (r < 0) r += 4;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            out[i][j] = FORMAS[tipo][r][i][j];
}
