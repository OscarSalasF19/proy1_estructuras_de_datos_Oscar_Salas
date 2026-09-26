#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <SFML/Graphics.hpp>

const int FILAS = 20;
const int COLUMNAS = 10;

const int TAM_CELDA = 28;
const int ANCHO_TABLERO_PX = COLUMNAS * TAM_CELDA;
const int ALTO_TABLERO_PX = FILAS * TAM_CELDA;

const int ANCHO_PANEL = 200;
const int MARGEN = 12;

const int ANCHO_VENTANA = ANCHO_TABLERO_PX + ANCHO_PANEL + MARGEN * 3;
const int ALTO_VENTANA = ALTO_TABLERO_PX + MARGEN * 2;

const int ORIGEN_TABLERO_X = MARGEN;
const int ORIGEN_TABLERO_Y = MARGEN;

const float TIEMPO_CAIDA_INICIAL_MS = 1000.0f;
const float TIEMPO_CAIDA_MIN_MS = 100.0f;
const float DECREMENTO_POR_NIVEL_MS = 80.0f;
const int LINEAS_POR_NIVEL = 10;

const float TIEMPO_ANIM_LINEA_MS = 200.0f;


const sf::Color COLOR_FONDO(20, 20, 35);
const sf::Color COLOR_TABLERO(35, 35, 55);
const sf::Color COLOR_REJILLA(50, 50, 70);
const sf::Color COLOR_TEXTO(235, 235, 245);
const sf::Color COLOR_FANTASMA(255, 255, 255, 60);

const sf::Color COLOR_I(0, 240, 240);
const sf::Color COLOR_O(240, 240, 0);
const sf::Color COLOR_T(160, 0, 240);
const sf::Color COLOR_S(0, 240, 0);
const sf::Color COLOR_Z(240, 0, 0);
const sf::Color COLOR_J(0, 0, 240);
const sf::Color COLOR_L(240, 160, 0);
const sf::Color COLOR_VACIO(0, 0, 0, 0);
const sf::Color COLOR_BORDE_CELDA(25, 25, 40);

const char* const ARCHIVO_PUNTAJES = "mejores_puntajes.txt";
const int TOP_PUNTAJES = 10;

#endif
