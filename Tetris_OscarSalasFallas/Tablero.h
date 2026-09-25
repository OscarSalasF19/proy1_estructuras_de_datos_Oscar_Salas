#ifndef TABLERO_H
#define TABLERO_H
#include <iostream>
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
	void limpiarLineasCompletas();
	bool estaOcupada(int fila, int celda);
	void imprimirConsola();
	~Tablero();

};

#endif

