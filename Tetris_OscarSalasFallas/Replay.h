#ifndef REPLAY_H
#define REPLAY_H
#include "EstadoJuego.h"
class Replay {
private:
	struct Nodo{
		EstadoJuego estado;
		Nodo* anterior;
		Nodo* siguiente;
	};
	Nodo* cabeza;
	Nodo* cola;
	Nodo* actual;
	int tam;
	void eliminarEstados(Nodo* estado);
public:
	Replay();
	~Replay();
	void agregarEstado(EstadoJuego* e);
	void deshacer();
	void rehacer();
	void reiniciar();
	void reproducirDesdeInicio();
	int getTam();
	bool puedeDeshacer();
	bool puedeRehacer();
	
};

#endif

