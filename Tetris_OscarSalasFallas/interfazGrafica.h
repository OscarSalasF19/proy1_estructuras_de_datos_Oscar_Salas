#ifndef INTERFAZGRAFICA_H
#define INTERFAZGRAFICA_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "Juego.h"
#include "Constantes.h"
#include "Puntaje.h"
using namespace std;

class interfazGrafica {
private:
	sf::RenderWindow ventana;
	sf::Font fuente;
	bool fuenteOK;
	sf::Clock relojCaida;
	sf::Texture texFondo;
	sf::Sprite sprFondo;
	bool fondoOK;
	float tiempoPartidaSegundos;

	bool cargarFuente();
	bool cargarFondo();
	void abrirVentana(string titulo);
	void dibujarFondo();
	void dibujarTablero(Juego& juego);
	void dibujarCelda(int fila, int col, sf::Color color);
	void dibujarPiezaActual(Juego& juego);
	void dibujarPanel(Juego& juego);
	void dibujarMiniPieza(TipoPieza tipo, float origenX, float origenY, float tamBloque);
	void dibujarTexto(string contenido, float posX, float posY, unsigned tamLetra);
	void dibujarTextoC(string contenido, float centroX, float posY, unsigned tamLetra);
	void dibujarBoton(float posX, float posY, float ancho, float alto, string etiqueta, unsigned tamLetra = 20);
	bool sobreBoton(float posX, float posY, float ancho, float alto, sf::Vector2i puntoClic);
	void manejarTeclado(Juego& juego, sf::Keyboard::Key tecla);
	void actualizarCaida(Juego& juego);
	int jugarPartida(int nivelInicial, string& resultadoOut, Replay& replayOut);
	void guardarPuntaje(int puntos, string nombre = "JUGADOR");
	void dibujarTableroReplay(EstadoJuego* estado, float origenX, float origenY, float tamCelda);
	void animarLimpiezaLineas(Juego& juego);
	void dibujarOverlayPausa();

public:
	interfazGrafica();
	int ejecutar();
	int mostrarMenu();
	void mostrarEstadisticas();
	string mostrarPantallaFinal(string resultado, int puntaje, Replay& replay);
};

#endif
