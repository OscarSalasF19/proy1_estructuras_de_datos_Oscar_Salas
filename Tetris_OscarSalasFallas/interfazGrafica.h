#ifndef INTERFAZGRAFICA_H
#define INTERFAZGRAFICA_H

#include <SFML/Graphics.hpp>
#include "Juego.h"

class interfazGrafica {
private:
	sf::RenderWindow ventana;
	sf::Font fuente;
	bool fuenteOK;
	sf::Clock relojCaida;
	sf::Texture texFondo;
	sf::Sprite sprFondo;
	bool fondoOK;

	bool cargarFuente();
	bool cargarFondo();
	void dibujarFondo();
	void dibujarTablero(Juego& juego);
	void dibujarCelda(int fila, int col, sf::Color color);
	void dibujarPiezaActual(Juego& juego);
	void dibujarPanel(Juego& juego);
	void dibujarMiniPieza(TipoPieza tipo, float x, float y, float tam);
	void dibujarTexto(const std::string& str, float x, float y, unsigned tam);
	void manejarTeclado(Juego& juego, sf::Keyboard::Key tecla);
	void actualizarCaida(Juego& juego);

public:
	interfazGrafica();
	int ejecutar();
};

#endif
