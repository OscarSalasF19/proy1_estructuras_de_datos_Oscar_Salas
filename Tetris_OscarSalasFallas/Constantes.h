#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <SFML/Graphics.hpp>

const int FILAS = 20;
const int COLUMNAS = 10;

const int TAM_CELDA = 40;
const int ANCHO_TABLERO_PX = COLUMNAS * TAM_CELDA;
const int ALTO_TABLERO_PX = FILAS * TAM_CELDA;

const int ANCHO_PANEL = 200;
const int MARGEN = 12;

const int ANCHO_VENTANA = 900;
const int ALTO_VENTANA = 900;

const int ORIGEN_TABLERO_X = (ANCHO_VENTANA - (ANCHO_TABLERO_PX + MARGEN + ANCHO_PANEL)) / 2;
const int ORIGEN_TABLERO_Y = (ALTO_VENTANA - ALTO_TABLERO_PX) / 2;

const float TIEMPO_CAIDA_INICIAL_MS = 1000.0f;
const float TIEMPO_CAIDA_MIN_MS = 100.0f;
const float DECREMENTO_POR_NIVEL_MS = 80.0f;
const int LINEAS_POR_NIVEL = 10;

const float TIEMPO_ANIM_LINEA_MS = 200.0f;


const sf::Color COLOR_FONDO(5, 8, 16);
const sf::Color COLOR_TABLERO(8, 15, 30);
const sf::Color COLOR_REJILLA(15, 40, 70);
const sf::Color COLOR_TEXTO(190, 245, 255);
const sf::Color COLOR_TITULO(0, 229, 255);
const sf::Color COLOR_FANTASMA(0, 229, 255, 60);
const sf::Color COLOR_FIJA(10, 45, 80);
const sf::Color COLOR_MARCO_NEON(0, 229, 255);

const sf::Color COLOR_I(0, 229, 255);
const sf::Color COLOR_O(220, 250, 255);
const sf::Color COLOR_T(0, 150, 255);
const sf::Color COLOR_S(0, 255, 209);
const sf::Color COLOR_Z(255, 122, 0);
const sf::Color COLOR_J(30, 80, 255);
const sf::Color COLOR_L(255, 170, 0);
const sf::Color COLOR_VACIO(0, 0, 0, 0);
const sf::Color COLOR_BORDE_CELDA(0, 229, 255);

const char* const ARCHIVO_PUNTAJES = "mejores_puntajes.txt";
const int TOP_PUNTAJES = 10;

#endif
