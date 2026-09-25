#ifndef COLAEVENTOS_H
#define COLAEVENTOS_H

#include <string>

enum TipoEvento {
	EV_AUMENTO_VELOCIDAD = 0,
	EV_PIEZA_ESPECIAL = 1,
	EV_BONUS_PUNTAJE = 2
};

struct Evento {
	TipoEvento tipo;
	int momentoDisparo;
	std::string descripcion;
};

class ColaEventos {
private:
	struct Nodo {
		Evento dato;
		Nodo* siguiente;
	};
	Nodo* cabeza;
	int tam;
	
public:
	ColaEventos();
	~ColaEventos();
	
	void programar(Evento e);
	bool proximo(Evento& eSalida);
	bool debeDispararse(int tiempoActual);
	bool disparar(Evento& eSalida);
	bool vacia();
	int getTam();
};

#endif
