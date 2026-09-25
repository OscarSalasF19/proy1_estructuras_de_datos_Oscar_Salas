#include "Pieza.h"

// ============================================================
// FORMAS[7][4][4][4]
// Cada pieza 4x4, 4 rotaciones precalculadas.
// Visualmente (1 = #):
//
// I rot0: ####      I rot1: #
//                        #
//                        #
//                        #
// O rot*: ##
//         ##   (igual 4 rotaciones)
// T rot0:  #       T rot1: #
//         ###            ##
//                        #
// S rot0:  ##      S rot1: #
//         ##             ##
//                         #
// Z rot0: ##       Z rot1:  #
//          ##           ##
//                       #
// J rot0: #        J rot1: ##
//         ###            #
//                        #
// L rot0:   #      L rot1: #
//         ###            #
//                       ##
// ============================================================
const int FORMAS[7][4][4][4] = {
    // I = 0
    {
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}, // rot0 horizontal
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}, // rot1 vertical
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}, // rot2 = rot0
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}  // rot3 = rot1
    },
    // O = 1
    {
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
    },
    // T = 2
    {
        {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}, // rot0
        {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}, // rot1
        {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}}, // rot2
        {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}  // rot3
    },
    // S = 3
    {
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}, // rot0
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}, // rot1
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}, // rot2 = rot0
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}  // rot3 = rot1
    },
    // Z = 4
    {
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}, // rot0
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}, // rot1
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}, // rot2 = rot0
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}  // rot3 = rot1
    },
    // J = 5
    {
        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}, // rot0
        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}, // rot1
        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}}, // rot2
        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}  // rot3
    },
    // L = 6
    {
        {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}, // rot0
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}, // rot1
        {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}}, // rot2
        {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}  // rot3
    }
};

// ============================================================
// Constructores
// ============================================================
Pieza::Pieza(){
	this->tipo = NINGUNA;
	this->rotacion = 0;
	this->x = 3;
	this->y = 0;
}

Pieza::Pieza(TipoPieza t) : tipo(t), rotacion(0), x(3), y(0) {
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

// ============================================================
// Getters
// ============================================================
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

// ============================================================
// Movimiento / rotacion
// ============================================================
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

// ============================================================
// Matriz 4x4 de la pieza
// Copia la matriz de FORMAS a out[4][4] para que Tablero
// pueda iterar sin acceder directo a FORMAS.
// ============================================================
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
