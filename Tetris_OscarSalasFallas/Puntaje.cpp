#include "Puntaje.h"

Puntaje::Puntaje() {
	tam = 0;
	historico = nullptr;
}

void Puntaje::insertarPuntaje(int puntos, string jugador, string fecha){
	int tamAnterior = tam;
	this->tam++;
	Marcador* aux = historico;
	historico = new Marcador[tam];
	for(int i = 0; i < tamAnterior; i++){
		historico[i] = aux[i];
	}
	Marcador nuevo = Marcador{jugador, puntos, fecha};
	historico[tam-1] = nuevo;
	delete[] aux;
}
void Puntaje::selectionSort(){
	for(int i = 0; i < tam; i ++){
		Marcador valorMax = historico[i];
		int posMax = i;
		for(int j = i+1; j < tam; j++){
			if(historico[j].puntos > valorMax.puntos){
				valorMax = historico[j];
				posMax = j;
			}
		}
		Marcador aux = historico[i];
		historico[i] = valorMax;
		historico[posMax] = aux;
	}
}
void Puntaje::merge(int inicio, int medio, int final){
	int sizeIzquierda = medio - inicio + 1;
	int sizeDerecha = final - medio;
	Marcador* izquierda = new Marcador[sizeIzquierda];
	Marcador* derecha = new Marcador[sizeDerecha];
	for(int i = 0; i < sizeIzquierda;  i++){
		izquierda[i] = this->historico[inicio + i]; 
	}
	for(int i = 0; i < sizeDerecha;  i++){
		derecha[i] = this->historico[medio + 1 + i]; 
	}
	
	int i = 0; 
	int j = 0;
	int k = inicio;
	while(i < sizeIzquierda && j < sizeDerecha){
		if(izquierda[i].puntos >= derecha[j].puntos){
			historico[k] = izquierda[i];
			i++;
		}else{
			historico[k] = derecha[j];
			j++;
		}
		k++;
	}
	while (i < sizeIzquierda) {
		historico[k] = izquierda[i];
		i++;
		k++;
	}
	while (j < sizeDerecha) {
		historico[k] = derecha[j];
		j++;
		k++;
	}
	delete[] derecha;
	delete[] izquierda;
	
}

void Puntaje::mergeSort(int inicio, int final){
	if(inicio >= final){
		return;
	}
	int medio = inicio + (final - inicio)/2;
	mergeSort(inicio, medio);
	mergeSort(medio + 1, final);
	merge(inicio, medio, final);
}

void Puntaje::iniciarMergeSort(){
	mergeSort(0, tam-1);
}
