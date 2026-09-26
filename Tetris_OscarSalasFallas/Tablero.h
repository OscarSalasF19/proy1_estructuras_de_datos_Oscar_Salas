#ifndef TABLERO_H
#define TABLERO_H
#include <iostream>
#include"Pieza.h"
#include"Constantes.h"
class Tablero {
private:
	struct Fila{
		int celdas[10];
		Fila* siguiente;
	};
	Fila* cabeza;
	int numFilas = 20;
public:
	Tablero();
	void crearTableroVacio();
	void copiarDesde(Tablero& origen);
	int getCelda(int indice, int celda);
	void setCelda(int fila, int celda, int valor);
	bool esFilaCompleta(int indice);
	bool eliminarFila(int indice);
	void insertarFilaVaciaAlInicio();
	int limpiarLineasCompletas();
	bool estaOcupada(int fila, int celda);
	void imprimirConsola();
	~Tablero();
	bool puedeColocar(Pieza* p);
	void insertaPieza(Pieza* p);
	void limpiarPieza(Pieza* p);

};

#endif

