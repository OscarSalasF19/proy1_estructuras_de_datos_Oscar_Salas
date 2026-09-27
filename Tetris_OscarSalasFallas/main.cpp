#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "interfazGrafica.h"
using namespace std;

int main(int argc, char *argv[]){
	srand((unsigned)time(0));
	interfazGrafica app;
	return app.ejecutar();
}
