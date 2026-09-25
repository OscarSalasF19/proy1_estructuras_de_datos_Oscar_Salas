#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <SFML/Graphics.hpp>

// ============================================================
// Dimensiones del tablero (R5 - Lista enlazada de 20 nodos)
// ============================================================
const int FILAS = 20;
const int COLUMNAS = 10;

// ============================================================
// Ventana y render (R8 - SFML)
// ============================================================
const int TAM_CELDA = 28;                 // pixeles por celda
const int ANCHO_TABLERO_PX = COLUMNAS * TAM_CELDA;
const int ALTO_TABLERO_PX = FILAS * TAM_CELDA;

const int ANCHO_PANEL = 200;              // panel lateral para siguientes/hold/puntaje
const int MARGEN = 12;

const int ANCHO_VENTANA = ANCHO_TABLERO_PX + ANCHO_PANEL + MARGEN * 3;
const int ALTO_VENTANA = ALTO_TABLERO_PX + MARGEN * 2;

// Origen del tablero dentro de la ventana
const int ORIGEN_TABLERO_X = MARGEN;
const int ORIGEN_TABLERO_Y = MARGEN;

// ============================================================
// Tiempos de juego (R7 caida + R4 eventos)
// ============================================================
const float TIEMPO_CAIDA_INICIAL_MS = 1000.0f; // 1 fila por segundo al iniciar
const float TIEMPO_CAIDA_MIN_MS = 100.0f;      // limite por eventos de velocidad
const float DECREMENTO_POR_NIVEL_MS = 80.0f;   // cuanto acelera por nivel
const int LINEAS_POR_NIVEL = 10;

const float TIEMPO_ANIM_LINEA_MS = 200.0f;     // parpadeo al limpiar

// ============================================================
// Puntaje (R6 - formula documentada en informe)
// ============================================================
// 1 linea = 100 * nivel, 2 = 300 * nivel, 3 = 500 * nivel, 4 (Tetris) = 800 * nivel
const int PUNTOS_1_LINEA = 100;
const int PUNTOS_2_LINEAS = 300;
const int PUNTOS_3_LINEAS = 500;
const int PUNTOS_4_LINEAS = 800;

// ============================================================
// Colores por pieza (SFML)
// ============================================================
const sf::Color COLOR_FONDO(20, 20, 35);
const sf::Color COLOR_TABLERO(35, 35, 55);
const sf::Color COLOR_REJILLA(50, 50, 70);
const sf::Color COLOR_TEXTO(235, 235, 245);
const sf::Color COLOR_FANTASMA(255, 255, 255, 60);

const sf::Color COLOR_I(0, 240, 240);   // cyan
const sf::Color COLOR_O(240, 240, 0);   // amarillo
const sf::Color COLOR_T(160, 0, 240);   // morado
const sf::Color COLOR_S(0, 240, 0);     // verde
const sf::Color COLOR_Z(240, 0, 0);     // rojo
const sf::Color COLOR_J(0, 0, 240);     // azul
const sf::Color COLOR_L(240, 160, 0);   // naranja
const sf::Color COLOR_VACIO(0, 0, 0, 0);
const sf::Color COLOR_BORDE_CELDA(25, 25, 40);

// ============================================================
// Archivo de puntajes (R6)
// ============================================================
const char* const ARCHIVO_PUNTAJES = "mejores_puntajes.txt";
const int TOP_PUNTAJES = 10;

#endif
