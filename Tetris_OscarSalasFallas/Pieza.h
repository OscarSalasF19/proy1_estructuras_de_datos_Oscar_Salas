#ifndef PIEZA_H
#define PIEZA_H

#include <SFML/Graphics.hpp>
#include "Constantes.h"

// ============================================================
// Tipo de pieza (enum = int con nombre)
// Cada valor es indice para la tabla FORMAS[7][4][4][4]
// ============================================================
enum TipoPieza {
    I = 0,
    O = 1,
    T = 2,
    S = 3,
    Z = 4,
    J = 5,
    L = 6,
    NINGUNA = 7 // usado en Hold vacio
};

// ============================================================
// Tabla estatica precalculada: [tipo][rotacion 0..3][fila 0..3][col 0..3]
// 1 = bloque ocupado, 0 = vacio
// Sistema sin wall kick: rotar solo si hay espacio
// ============================================================
extern const int FORMAS[7][4][4][4];

// ============================================================
// Clase Pieza
// Representa una instancia activa en el tablero (tipo + rot + x,y)
// ============================================================
class Pieza {
	private:
	TipoPieza tipo;
	int rotacion; // 0..3
	int x; // columna en tablero (0..COLUMNAS-1) - ancla esquina sup-izq del 4x4
	int y; // fila en tablero (0..FILAS-1)
	
public:
    Pieza();
    Pieza(TipoPieza t);
    Pieza(TipoPieza t, int rot, int px, int py);

    // Getters
    TipoPieza getTipo();
    int getRotacion();
    int getX();
    int getY();
    sf::Color getColor();
    static sf::Color getColorPorTipo(TipoPieza t);

    // Setters / movimiento
    void setPosicion(int px, int py);
    void mover(int dx, int dy);
    void setRotacion(int r); // 0..3 normalizado
    void rotarHorario();     // r = (r+1)%4
    void rotarAntiHorario(); // r = (r+3)%4

    // Acceso a la matriz 4x4 de la rotacion actual
    void getMatriz(int out[4][4]);
    void getMatrizRot(int rot, int out[4][4]);

    // Utilidad
    bool esVacia();
};

#endif

