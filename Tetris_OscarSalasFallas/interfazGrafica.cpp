#include "interfazGrafica.h"
#include "Constantes.h"
#include <string>

interfazGrafica::interfazGrafica() {
	fuenteOK = false;
	fondoOK = false;
}

bool interfazGrafica::cargarFuente() {
	if (fuente.loadFromFile("resources/fonts/batmfa__.ttf")) return true;
	if (fuente.loadFromFile("./resources/fonts/batmfa__.ttf")) return true;
	if (fuente.loadFromFile("../resources/fonts/batmfa__.ttf")) return true;
	if (fuente.loadFromFile("Tetris_OscarSalasFallas/resources/fonts/batmfa__.ttf")) return true;
	if (fuente.loadFromFile("resources/fonts/batmfo__.ttf")) return true;
	if (fuente.loadFromFile("./resources/fonts/batmfo__.ttf")) return true;
	if (fuente.loadFromFile("../resources/fonts/batmfo__.ttf")) return true;
	if (fuente.loadFromFile("arial.ttf")) return true;
	if (fuente.loadFromFile("C:/Windows/Fonts/arial.ttf")) return true;
	return false;
}

bool interfazGrafica::cargarFondo() {
	const char* rutas[] = {
		"resources/images/background.jpg",
		"./resources/images/background.jpg",
		"../resources/images/background.jpg",
		"Tetris_OscarSalasFallas/resources/images/background.jpg"
	};
	for (int i = 0; i < 4; i++) {
		if (texFondo.loadFromFile(rutas[i])) {
			texFondo.setSmooth(true);
			sf::Vector2u t = texFondo.getSize();
			if (t.x > 0 && t.y > 0) {
				sprFondo.setTexture(texFondo);
				sprFondo.setScale((float)ANCHO_VENTANA / (float)t.x,
				                  (float)ALTO_VENTANA / (float)t.y);
			}
			return true;
		}
	}
	return false;
}

void interfazGrafica::dibujarFondo() {
	if (!fondoOK) return;
	ventana.draw(sprFondo);
	sf::RectangleShape velo(sf::Vector2f((float)ANCHO_VENTANA, (float)ALTO_VENTANA));
	velo.setPosition(0, 0);
	velo.setFillColor(sf::Color(5, 8, 16, 130));
	ventana.draw(velo);
}

void interfazGrafica::dibujarCelda(int fila, int col, sf::Color color) {
	float x = (float)(ORIGEN_TABLERO_X + col * TAM_CELDA);
	float y = (float)(ORIGEN_TABLERO_Y + fila * TAM_CELDA);
	sf::RectangleShape base(sf::Vector2f((float)TAM_CELDA - 1, (float)TAM_CELDA - 1));
	base.setPosition(x + 1, y + 1);
	base.setFillColor(color);
	base.setOutlineColor(COLOR_BORDE_CELDA);
	base.setOutlineThickness(1);
	ventana.draw(base);
}

void interfazGrafica::dibujarTablero(Juego& juego) {
	sf::RectangleShape marco(sf::Vector2f((float)ANCHO_TABLERO_PX + 4, (float)ALTO_TABLERO_PX + 4));
	marco.setPosition((float)ORIGEN_TABLERO_X - 2, (float)ORIGEN_TABLERO_Y - 2);
	marco.setFillColor(sf::Color::Transparent);
	marco.setOutlineColor(COLOR_MARCO_NEON);
	marco.setOutlineThickness(2);
	ventana.draw(marco);

	sf::RectangleShape fondo(sf::Vector2f((float)ANCHO_TABLERO_PX, (float)ALTO_TABLERO_PX));
	fondo.setPosition((float)ORIGEN_TABLERO_X, (float)ORIGEN_TABLERO_Y);
	fondo.setFillColor(COLOR_TABLERO);
	ventana.draw(fondo);

	Tablero& t = juego.getTablero();
	for (int f = 0; f < FILAS; f++) {
		for (int c = 0; c < COLUMNAS; c++) {
			int v = t.getCelda(f, c);
			if (v == 1) {
				dibujarCelda(f, c, COLOR_FIJA);
			} else {
				
				sf::RectangleShape g(sf::Vector2f((float)TAM_CELDA - 1, (float)TAM_CELDA - 1));
				g.setPosition((float)(ORIGEN_TABLERO_X + c * TAM_CELDA + 1),
				              (float)(ORIGEN_TABLERO_Y + f * TAM_CELDA + 1));
				g.setFillColor(sf::Color::Transparent);
				g.setOutlineColor(COLOR_REJILLA);
				g.setOutlineThickness(1);
				ventana.draw(g);
			}
		}
	}
}

void interfazGrafica::dibujarPiezaActual(Juego& juego) {
	Pieza* p = juego.getActual();
	if (!p) return;
	if (p->esVacia()) return;
	int mat[4][4];
	p->getMatriz(mat);
	sf::Color col = Pieza::getColorPorTipo(p->getTipo());
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (mat[i][j] == 1) {
				int fy = p->getY() + i;
				int fx = p->getX() + j;
				if (fy < 0 || fy >= FILAS || fx < 0 || fx >= COLUMNAS) continue;
				dibujarCelda(fy, fx, col);
			}
		}
	}
}

void interfazGrafica::dibujarMiniPieza(TipoPieza tipo, float x, float y, float tam) {
	if (tipo == NINGUNA) return;
	int mat[4][4];
	Pieza tmp(tipo);
	tmp.getMatriz(mat);
	sf::Color col = Pieza::getColorPorTipo(tipo);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (mat[i][j] == 1) {
				sf::RectangleShape r(sf::Vector2f(tam - 1, tam - 1));
				r.setPosition(x + j * tam + 1, y + i * tam + 1);
				r.setFillColor(col);
				r.setOutlineColor(COLOR_BORDE_CELDA);
				r.setOutlineThickness(1);
				ventana.draw(r);
			}
		}
	}
}

void interfazGrafica::dibujarTexto(const std::string& str, float x, float y, unsigned tam) {
	if (!fuenteOK) return;
	sf::Text t;
	t.setFont(fuente);
	t.setString(str);
	t.setCharacterSize(tam);
	t.setFillColor(tam >= 20 ? COLOR_TITULO : COLOR_TEXTO);
	t.setPosition(x, y);
	ventana.draw(t);
}

void interfazGrafica::dibujarPanel(Juego& juego) {
	float px = (float)(ORIGEN_TABLERO_X + ANCHO_TABLERO_PX + MARGEN);
	float py = (float)ORIGEN_TABLERO_Y;

	dibujarTexto("Puntos", px, py, 16); py += 20;
	dibujarTexto(std::to_string(juego.getPuntaje()), px, py, 20); py += 34;

	dibujarTexto("Lineas", px, py, 16); py += 20;
	dibujarTexto(std::to_string(juego.getLineas()), px, py, 20); py += 34;

	dibujarTexto("Nivel", px, py, 16); py += 20;
	dibujarTexto(std::to_string(juego.getNivel()), px, py, 20); py += 34;

	dibujarTexto("Hold (C)", px, py, 16); py += 22;
	if (!juego.getHold().vacia()) {
		dibujarMiniPieza(juego.getHold().top(), px, py, 18);
	}
	py += 90;

	dibujarTexto("Siguiente", px, py, 16); py += 22;
	if (juego.getSiguiente()) {
		dibujarMiniPieza(juego.getSiguiente()->getTipo(), px, py, 18);
	}
	py += 90;

	TipoPieza* prox = juego.getCola().proximas3();
	if (prox) {
		dibujarTexto("Cola", px, py, 16); py += 22;
		for (int i = 0; i < 3; i++) {
			dibujarMiniPieza(prox[i], px, py, 14);
			py += 62;
		}
		delete[] prox;
	}

	if (juego.getGameOver()) {
		dibujarTexto("GAME OVER", px, py + 10, 20);
	} else if (juego.getWin()) {
		dibujarTexto("WIN", px, py + 10, 20);
	}
}

void interfazGrafica::manejarTeclado(Juego& juego, sf::Keyboard::Key tecla) {
	if (juego.getGameOver() || juego.getWin()) return;
	if (!juego.getActual()) return;
	switch (tecla) {
		case sf::Keyboard::Left: juego.moverIzquierda(); break;
		case sf::Keyboard::Right: juego.moverDerecha(); break;
		case sf::Keyboard::Down: juego.bajar(); relojCaida.restart(); break;
		case sf::Keyboard::Up: juego.rotarHorario(); break;
		case sf::Keyboard::Z: juego.rotarAntiHorario(); break;
		case sf::Keyboard::Space: juego.hardDrop(); relojCaida.restart(); break;
		case sf::Keyboard::C: juego.intercambiarHold(); break;
		case sf::Keyboard::U: juego.deshacer(); break;
		case sf::Keyboard::R: juego.rehacer(); break;
		default: break;
	}
}

void interfazGrafica::actualizarCaida(Juego& juego) {
	if (juego.getGameOver() || juego.getWin()) return;
	if (!juego.getActual()) return;
	float intervalo = juego.getTiempoCaida();
	if (relojCaida.getElapsedTime().asMilliseconds() >= intervalo) {
		juego.bajar();
		relojCaida.restart();
	}
}

int interfazGrafica::ejecutar() {
	Juego juego;
	juego.iniciar();

	ventana.create(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "TRON: Tetris Legacy - T3.1");
	ventana.setFramerateLimit(60);
	fuenteOK = cargarFuente();
	fondoOK = cargarFondo();
	relojCaida.restart();

	while (ventana.isOpen()) {
		sf::Event e;
		while (ventana.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				ventana.close();
			} else if (e.type == sf::Event::KeyPressed) {
				manejarTeclado(juego, e.key.code);
			}
		}
		actualizarCaida(juego);

		ventana.clear(COLOR_FONDO);
		dibujarFondo();
		dibujarTablero(juego);
		dibujarPiezaActual(juego);
		dibujarPanel(juego);
		ventana.display();
	}
	return 0;
}
