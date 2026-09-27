#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include "Constantes.h"
using namespace std;
class Puntaje {
private:
	struct Marcador{
		string nombreJugador;
		int puntos;
		string fecha;
	};
	Marcador* historico;
	int tam;
public:
	Puntaje();
	~Puntaje();
	void insertarPuntaje(int puntos, string jugador, string fecha);
	void selectionSort();
	void mergeSort(int inicio, int final);
	void merge(int inicio, int medio, int final);
	void iniciarMergeSort();
	string getNombre(int indice);
	int getPuntos(int indice);
	string getFecha(int indice);
	int getTam();
};
#endif

