#include "interfazGrafica.h"

interfazGrafica::interfazGrafica() {
	fuenteOK = false;
	fondoOK = false;
	tiempoPartidaSegundos = 0.0f;
}

bool interfazGrafica::cargarFuente() {
	if (fuente.loadFromFile("resources/fonts/batmfa__.ttf")){
		return true;
	}
	return false;
}

bool interfazGrafica::cargarFondo() {
	if (texFondo.loadFromFile("resources/images/background.jpg")) {
	texFondo.setSmooth(true);
	sf::Vector2u dimensionesTextura = texFondo.getSize();
	if (dimensionesTextura.x > 0 && dimensionesTextura.y > 0) {
		sprFondo.setTexture(texFondo);
		sprFondo.setScale((float)ANCHO_VENTANA / (float)dimensionesTextura.x,
			(float)ALTO_VENTANA / (float)dimensionesTextura.y);
		}
		return true;
	}
	return false;
}

void interfazGrafica::dibujarFondo() {
	if (!fondoOK){
		return;
	}
	ventana.draw(sprFondo);
}

void interfazGrafica::dibujarCelda(int fila, int col, sf::Color color) {
	float posX = (float)(ORIGEN_TABLERO_X + col * TAM_CELDA);
	float posY = (float)(ORIGEN_TABLERO_Y + fila * TAM_CELDA);
	sf::RectangleShape bloque(sf::Vector2f((float)TAM_CELDA - 1, (float)TAM_CELDA - 1));
	bloque.setPosition(posX + 1, posY + 1);
	bloque.setFillColor(color);
	bloque.setOutlineColor(COLOR_BORDE_CELDA);
	bloque.setOutlineThickness(1);
	ventana.draw(bloque);
}

void interfazGrafica::dibujarTablero(Juego& juego) {
	sf::RectangleShape marcoNeon(sf::Vector2f((float)ANCHO_TABLERO_PX + 4, (float)ALTO_TABLERO_PX + 4));
	marcoNeon.setPosition((float)ORIGEN_TABLERO_X - 2, (float)ORIGEN_TABLERO_Y - 2);
	marcoNeon.setFillColor(sf::Color::Transparent);
	marcoNeon.setOutlineColor(COLOR_MARCO_NEON);
	marcoNeon.setOutlineThickness(2);
	ventana.draw(marcoNeon);

	sf::RectangleShape fondoTablero(sf::Vector2f((float)ANCHO_TABLERO_PX, (float)ALTO_TABLERO_PX));
	fondoTablero.setPosition((float)ORIGEN_TABLERO_X, (float)ORIGEN_TABLERO_Y);
	fondoTablero.setFillColor(COLOR_TABLERO);
	ventana.draw(fondoTablero);

	Tablero& tablero = juego.getTablero();
	for (int fila = 0; fila < FILAS; fila++) {
		for (int columna = 0; columna < COLUMNAS; columna++) {
			int valorCelda = tablero.getCelda(fila, columna);
			if (valorCelda == 1) {
				dibujarCelda(fila, columna, COLOR_FIJA);
			} else {
				sf::RectangleShape celdaVacia(sf::Vector2f((float)TAM_CELDA - 1, (float)TAM_CELDA - 1));
				celdaVacia.setPosition((float)(ORIGEN_TABLERO_X + columna * TAM_CELDA + 1),
				                       (float)(ORIGEN_TABLERO_Y + fila * TAM_CELDA + 1));
				celdaVacia.setFillColor(sf::Color::Transparent);
				celdaVacia.setOutlineColor(COLOR_REJILLA);
				celdaVacia.setOutlineThickness(1);
				ventana.draw(celdaVacia);
			}
		}
	}
}

void interfazGrafica::dibujarPiezaActual(Juego& juego) {
	Pieza* piezaActual = juego.getActual();
	if (!piezaActual){
		return;
	}
	if (piezaActual->esVacia()){
		return;
	}
	int matrizPieza[4][4];
	piezaActual->getMatriz(matrizPieza);
	sf::Color colorPieza = Pieza::getColorPorTipo(piezaActual->getTipo());
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrizPieza[i][j] == 1) {
				int filaTablero = piezaActual->getY() + i;
				int columnaTablero = piezaActual->getX() + j;
				if (filaTablero < 0 || filaTablero >= FILAS || columnaTablero < 0 || columnaTablero >= COLUMNAS) continue;
				dibujarCelda(filaTablero, columnaTablero, colorPieza);
			}
		}
	}
}

void interfazGrafica::dibujarMiniPieza(TipoPieza tipo, float origenX, float origenY, float tamBloque) {
	if (tipo == NINGUNA){
		return;
	}
	int matrizMini[4][4];
	Pieza piezaTemporal(tipo);
	piezaTemporal.getMatriz(matrizMini);
	sf::Color colorMini = Pieza::getColorPorTipo(tipo);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (matrizMini[i][j] == 1) {
				sf::RectangleShape bloqueMini(sf::Vector2f(tamBloque - 1, tamBloque - 1));
				bloqueMini.setPosition(origenX + j * tamBloque + 1, origenY + i * tamBloque + 1);
				bloqueMini.setFillColor(colorMini);
				bloqueMini.setOutlineColor(COLOR_BORDE_CELDA);
				bloqueMini.setOutlineThickness(1);
				ventana.draw(bloqueMini);
			}
		}
	}
}

void interfazGrafica::dibujarTexto(string contenido, float posX, float posY, unsigned tamLetra) {
	if (!fuenteOK){
		return;
	}
	sf::Text texto;
	texto.setFont(fuente);
	texto.setString(contenido);
	texto.setCharacterSize(tamLetra);
	texto.setFillColor(tamLetra >= 20 ? COLOR_TITULO : COLOR_TEXTO);
	texto.setPosition(posX, posY);
	ventana.draw(texto);
}

void interfazGrafica::dibujarTextoC(string contenido, float centroX, float posY, unsigned tamLetra) {
	if (!fuenteOK){
		return;
	}
	sf::Text textoCentrado;
	textoCentrado.setFont(fuente);
	textoCentrado.setString(contenido);
	textoCentrado.setCharacterSize(tamLetra);
	textoCentrado.setFillColor(tamLetra >= 32 ? COLOR_TITULO : COLOR_TEXTO);
	sf::FloatRect limites = textoCentrado.getLocalBounds();
	textoCentrado.setPosition(centroX - (limites.left + limites.width / 2), posY);
	ventana.draw(textoCentrado);
}

void interfazGrafica::dibujarBoton(float posX, float posY, float ancho, float alto, string etiqueta, unsigned tamLetra) {
	sf::Vector2i posicionMouseActual = sf::Mouse::getPosition(ventana);
	bool estaSobre = sobreBoton(posX, posY, ancho, alto, posicionMouseActual);
	sf::RectangleShape marcoBoton(sf::Vector2f(ancho, alto));
	marcoBoton.setPosition(posX, posY);
	marcoBoton.setFillColor(estaSobre ? sf::Color(0, 60, 90) : sf::Color(8, 20, 38, 220));
	marcoBoton.setOutlineColor(COLOR_MARCO_NEON);
	marcoBoton.setOutlineThickness(2);
	ventana.draw(marcoBoton);
	if (!fuenteOK){
		return;
	}
	sf::Text textoBoton;
	textoBoton.setFont(fuente);
	textoBoton.setString(etiqueta);
	textoBoton.setCharacterSize(tamLetra);
	textoBoton.setFillColor(COLOR_TEXTO);
	sf::FloatRect limitesEtiqueta = textoBoton.getLocalBounds();
	textoBoton.setPosition(posX + (ancho - limitesEtiqueta.width) / 2.0f - limitesEtiqueta.left,
	                       posY + (alto - limitesEtiqueta.height) / 2.0f - limitesEtiqueta.top);
	ventana.draw(textoBoton);
}

bool interfazGrafica::sobreBoton(float posX, float posY, float ancho, float alto, sf::Vector2i puntoClic) {
	return puntoClic.x >= posX && puntoClic.x <= posX + ancho && puntoClic.y >= posY && puntoClic.y <= posY + alto;
}

int interfazGrafica::mostrarMenu() {
	abrirVentana("TETRIS TRON");
	float centroX = (float)ANCHO_VENTANA / 2;
	float anchoBoton = 340, altoBoton = 62;
	float botonX = centroX - anchoBoton / 2;
	while (ventana.isOpen()) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed){
				return 0;
			}
			if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i puntoClic(evento.mouseButton.x, evento.mouseButton.y);
				if (sobreBoton(botonX, 360, anchoBoton, altoBoton, puntoClic)){
					return 1;
				}
				if (sobreBoton(botonX, 440, anchoBoton, altoBoton, puntoClic)) {
					 mostrarEstadisticas(); 
					 abrirVentana("TETRIS TRON"); 
				}
				if (sobreBoton(botonX, 520, anchoBoton, altoBoton, puntoClic)) {
					return 0;
				}
			}
		}
		ventana.clear(COLOR_FONDO);
		dibujarFondo();
		dibujarTextoC("TETRIS TRON", centroX, 150, 64);
		dibujarBoton(botonX, 360, anchoBoton, altoBoton, "JUGAR");
		dibujarBoton(botonX, 440, anchoBoton, altoBoton, "ESTADISTICA");
		dibujarBoton(botonX, 520, anchoBoton, altoBoton, "SALIR");
		ventana.display();
	}
	return 0;
}

void interfazGrafica::guardarPuntaje(int puntos, string nombre) {
	if (nombre.empty()) {
		nombre = "JUGADOR";
	}
	time_t marcaTiempo = time(0);
	char fechaTexto[16] = "sin-fecha";
	if (marcaTiempo != (time_t)-1) {
		tm* infoFecha = localtime(&marcaTiempo);
		if (infoFecha) strftime(fechaTexto, sizeof(fechaTexto), "%d-%m-%Y", infoFecha);
	}
	ofstream archivoSalida(ARCHIVO_PUNTAJES, ios::app);
	if (archivoSalida){
		archivoSalida << puntos << "|" << nombre << "|" << fechaTexto << "\n";
	}
}

void interfazGrafica::mostrarEstadisticas() {
	float centroX = (float)ANCHO_VENTANA / 2.0f;
	float anchoBoton = 360.0f;
	float altoBoton = 60.0f;
	float botonX = centroX - anchoBoton / 2.0f;

	while (ventana.isOpen()) {
		abrirVentana("TETRIS TRON - METODO DE ORDENAMIENTO");
		string metodoElegido = "";

		while (ventana.isOpen() && metodoElegido.empty()) {
			sf::Event evento;
			while (ventana.pollEvent(evento)) {
				if (evento.type == sf::Event::Closed) {
					return;
				}
				if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i puntoClic(evento.mouseButton.x, evento.mouseButton.y);
					if (sobreBoton(botonX, 350.0f, anchoBoton, altoBoton, puntoClic)) {
						metodoElegido = "SELECTION SORT";
					}
					if (sobreBoton(botonX, 440.0f, anchoBoton, altoBoton, puntoClic)) {
						metodoElegido = "MERGE SORT";
					}
					if (sobreBoton(botonX, 550.0f, anchoBoton, altoBoton, puntoClic)) {
						return;
					}
				}
			}

			ventana.clear(COLOR_FONDO);
			dibujarFondo();
			dibujarTextoC("ESTADISTICAS", centroX, 130.0f, 52);
			dibujarTextoC("SELECCIONE EL METODO DE ORDENAMIENTO:", centroX, 250.0f, 22);

			dibujarBoton(botonX, 350.0f, anchoBoton, altoBoton, "SELECTION SORT", 20);
			dibujarBoton(botonX, 440.0f, anchoBoton, altoBoton, "MERGE SORT", 20);
			dibujarBoton(botonX, 550.0f, anchoBoton, altoBoton, "VOLVER", 20);

			ventana.display();
		}

		if (metodoElegido.empty()) {
			return;
		}

		Puntaje tablaPuntajes;
		ifstream archivoEntrada(ARCHIVO_PUNTAJES);
		if (archivoEntrada) {
			string lineaRegistro;
			while (getline(archivoEntrada, lineaRegistro)) {
				if (lineaRegistro.empty()) continue;
				int posSeparador1 = (int)lineaRegistro.find('|');
				int posSeparador2 = (int)lineaRegistro.find('|', posSeparador1 + 1);
				if (posSeparador1 < 0 || posSeparador2 < 0) continue;
				string textoPuntos = lineaRegistro.substr(0, posSeparador1);
				string nombreJugador = lineaRegistro.substr(posSeparador1 + 1, posSeparador2 - posSeparador1 - 1);
				string fechaRegistro = lineaRegistro.substr(posSeparador2 + 1);
				int valorPuntos = 0;
				try {
					valorPuntos = stoi(textoPuntos);
				} catch (...) {
					continue;
				}
				tablaPuntajes.insertarPuntaje(valorPuntos, nombreJugador, fechaRegistro);
			}
		}

		if (metodoElegido == "SELECTION SORT") {
			tablaPuntajes.selectionSort();
		} else {
			tablaPuntajes.iniciarMergeSort();
		}

		abrirVentana("TETRIS TRON - TOP 10 (" + metodoElegido + ")");
		bool volverASeleccion = false;

		float anchoCuadro = 760.0f;
		float altoCuadro = 520.0f;
		float cuadroX = centroX - anchoCuadro / 2.0f;
		float cuadroY = 160.0f;
		float altoHeader = 46.0f;

		while (ventana.isOpen() && !volverASeleccion) {
			sf::Event evento;
			while (ventana.pollEvent(evento)) {
				if (evento.type == sf::Event::Closed) {
					return;
				}
				if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i puntoClic(evento.mouseButton.x, evento.mouseButton.y);
					if (sobreBoton(centroX - 285.0f, 715.0f, 270.0f, 54.0f, puntoClic)) {
						volverASeleccion = true;
					}
					if (sobreBoton(centroX + 15.0f, 715.0f, 270.0f, 54.0f, puntoClic)) {
						return;
					}
				}
			}

			ventana.clear(COLOR_FONDO);
			dibujarFondo();

			dibujarTextoC("TOP 10 MEJORES PUNTAJES", centroX, 60.0f, 40);
			dibujarTextoC("ORDENADO POR: " + metodoElegido, centroX, 115.0f, 20);

			sf::RectangleShape marcoCuadro(sf::Vector2f(anchoCuadro, altoCuadro));
			marcoCuadro.setPosition(cuadroX, cuadroY);
			marcoCuadro.setFillColor(sf::Color(8, 20, 38, 230));
			marcoCuadro.setOutlineColor(COLOR_MARCO_NEON);
			marcoCuadro.setOutlineThickness(2.0f);
			ventana.draw(marcoCuadro);

			sf::RectangleShape barraHeader(sf::Vector2f(anchoCuadro, altoHeader));
			barraHeader.setPosition(cuadroX, cuadroY);
			barraHeader.setFillColor(sf::Color(0, 60, 90, 220));
			ventana.draw(barraHeader);

			sf::RectangleShape lineaSeparador(sf::Vector2f(anchoCuadro, 2.0f));
			lineaSeparador.setPosition(cuadroX, cuadroY + altoHeader);
			lineaSeparador.setFillColor(COLOR_MARCO_NEON);
			ventana.draw(lineaSeparador);

			float headerTextoY = cuadroY + 12.0f;
			dibujarTexto("POS", cuadroX + 35.0f, headerTextoY, 20);
			dibujarTexto("JUGADOR", cuadroX + 150.0f, headerTextoY, 20);
			dibujarTexto("PUNTAJE", cuadroX + 410.0f, headerTextoY, 20);
			dibujarTexto("FECHA", cuadroX + 600.0f, headerTextoY, 20);

			int cantidadRegistros = tablaPuntajes.getTam();
			if (cantidadRegistros == 0) {
				dibujarTextoC("NO HAY REGISTROS DE PUNTAJE", centroX, cuadroY + 220.0f, 22);
			} else {
				int topeMostrado = cantidadRegistros < TOP_PUNTAJES ? cantidadRegistros : TOP_PUNTAJES;
				float altoFila = 44.0f;
				for (int i = 0; i < topeMostrado; i++) {
					float filaY = cuadroY + altoHeader + 4.0f + (float)i * altoFila;

					if (i % 2 == 1) {
						sf::RectangleShape filaSombra(sf::Vector2f(anchoCuadro - 6.0f, altoFila - 2.0f));
						filaSombra.setPosition(cuadroX + 3.0f, filaY);
						filaSombra.setFillColor(sf::Color(15, 35, 60, 110));
						ventana.draw(filaSombra);
					}

					string posStr = to_string(i + 1);
					string jugadorStr = tablaPuntajes.getNombre(i);
					string puntosStr = to_string(tablaPuntajes.getPuntos(i));
					string fechaStr = tablaPuntajes.getFecha(i);

					dibujarTexto(posStr, cuadroX + 42.0f, filaY + 10.0f, 18);
					dibujarTexto(jugadorStr, cuadroX + 150.0f, filaY + 10.0f, 18);
					dibujarTexto(puntosStr, cuadroX + 410.0f, filaY + 10.0f, 18);
					dibujarTexto(fechaStr, cuadroX + 600.0f, filaY + 10.0f, 18);
				}
			}

			dibujarBoton(centroX - 285.0f, 715.0f, 270.0f, 54.0f, "CAMBIAR METODO", 18);
			dibujarBoton(centroX + 15.0f, 715.0f, 270.0f, 54.0f, "VOLVER AL MENU", 18);

			ventana.display();
		}
	}
}

void interfazGrafica::dibujarTableroReplay(EstadoJuego* estado, float origenX, float origenY, float tamCelda) {
	sf::RectangleShape marcoNeon(sf::Vector2f((float)COLUMNAS * tamCelda + 4, (float)FILAS * tamCelda + 4));
	marcoNeon.setPosition(origenX - 2, origenY - 2);
	marcoNeon.setFillColor(sf::Color::Transparent);
	marcoNeon.setOutlineColor(COLOR_MARCO_NEON);
	marcoNeon.setOutlineThickness(2);
	ventana.draw(marcoNeon);

	sf::RectangleShape fondoTablero(sf::Vector2f((float)COLUMNAS * tamCelda, (float)FILAS * tamCelda));
	fondoTablero.setPosition(origenX, origenY);
	fondoTablero.setFillColor(COLOR_TABLERO);
	ventana.draw(fondoTablero);

	if (!estado) {
		dibujarTextoC("Sin estado", origenX + (COLUMNAS * tamCelda) / 2, origenY + (FILAS * tamCelda) / 2, 20);
		return;
	}

	Tablero& tablero = estado->getTablero();
	for (int fila = 0; fila < FILAS; fila++) {
		for (int columna = 0; columna < COLUMNAS; columna++) {
			int valorCelda = tablero.getCelda(fila, columna);
			if (valorCelda == 1) {
				sf::RectangleShape bloque(sf::Vector2f(tamCelda - 1, tamCelda - 1));
				bloque.setPosition(origenX + columna * tamCelda + 1, origenY + fila * tamCelda + 1);
				bloque.setFillColor(COLOR_FIJA);
				bloque.setOutlineColor(COLOR_BORDE_CELDA);
				bloque.setOutlineThickness(1);
				ventana.draw(bloque);
			} else {
				sf::RectangleShape celdaVacia(sf::Vector2f(tamCelda - 1, tamCelda - 1));
				celdaVacia.setPosition(origenX + columna * tamCelda + 1, origenY + fila * tamCelda + 1);
				celdaVacia.setFillColor(sf::Color::Transparent);
				celdaVacia.setOutlineColor(COLOR_REJILLA);
				celdaVacia.setOutlineThickness(1);
				ventana.draw(celdaVacia);
			}
		}
	}

	Pieza p = estado->getPiezaActual();
	if (p.getTipo() != NINGUNA) {
		int matrizPieza[4][4];
		p.getMatriz(matrizPieza);
		sf::Color colorPieza = Pieza::getColorPorTipo(p.getTipo());
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (matrizPieza[i][j] == 1) {
					int filaTablero = p.getY() + i;
					int columnaTablero = p.getX() + j;
					if (filaTablero >= 0 && filaTablero < FILAS && columnaTablero >= 0 && columnaTablero < COLUMNAS) {
						sf::RectangleShape bloque(sf::Vector2f(tamCelda - 1, tamCelda - 1));
						bloque.setPosition(origenX + columnaTablero * tamCelda + 1, origenY + filaTablero * tamCelda + 1);
						bloque.setFillColor(colorPieza);
						bloque.setOutlineColor(COLOR_BORDE_CELDA);
						bloque.setOutlineThickness(1);
						ventana.draw(bloque);
					}
				}
			}
		}
	}
}

string interfazGrafica::mostrarPantallaFinal(string resultado, int puntaje, Replay& replay) {
	abrirVentana("TETRIS TRON - REPLAY");
	float centroX = (float)ANCHO_VENTANA / 2;
	bool esVictoria = (resultado == "victoria");
	string tituloFinal = esVictoria ? "VICTORIA" : "DERROTA";
	string textoAccion = esVictoria ? "SIGUIENTE NIVEL" : "JUGAR DE NUEVO";

	float tabX = 60.0f;
	float tabY = 120.0f;
	float tamCelda = 34.0f;

	float rx = 450.0f;
	float rw = 390.0f;
	float mitadW = (rw - 10.0f) / 2.0f;

	string nombreJugador = "";
	bool guardado = false;
	sf::Clock relojCursor;

	while (ventana.isOpen()) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				if (!guardado) {
					guardarPuntaje(puntaje, nombreJugador.empty() ? "JUGADOR" : nombreJugador);
					guardado = true;
				}
				return "salir";
			}
			if (evento.type == sf::Event::TextEntered) {
				if (evento.text.unicode == 8) {
					if (!nombreJugador.empty()) {
						nombreJugador.pop_back();
						guardado = false;
					}
				} else if (evento.text.unicode == 13 || evento.text.unicode == 10) {
					if (!guardado) {
						guardarPuntaje(puntaje, nombreJugador.empty() ? "JUGADOR" : nombreJugador);
						guardado = true;
					}
				} else if (evento.text.unicode >= 32 && evento.text.unicode <= 126 && evento.text.unicode != '|') {
					if (nombreJugador.size() < 12) {
						nombreJugador += (char)evento.text.unicode;
						guardado = false;
					}
				}
			}
			if (evento.type == sf::Event::KeyPressed) {
				if (evento.key.code == sf::Keyboard::Left) {
					replay.deshacer();
				} else if (evento.key.code == sf::Keyboard::Right) {
					replay.rehacer();
				}
			}
			if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i puntoClic(evento.mouseButton.x, evento.mouseButton.y);
				if (sobreBoton(rx, 305, mitadW, 42, puntoClic)) {
					replay.irAlInicio();
				}
				else if (sobreBoton(rx + mitadW + 10, 305, mitadW, 42, puntoClic)) {
					replay.irAlFinal();
				}
				else if (sobreBoton(rx, 355, mitadW, 42, puntoClic)) {
					replay.deshacer();
				}
				else if (sobreBoton(rx + mitadW + 10, 355, mitadW, 42, puntoClic)) {
					replay.rehacer();
				}
				else if (sobreBoton(rx, 505, rw, 42, puntoClic)) {
					if (!guardado) {
						guardarPuntaje(puntaje, nombreJugador.empty() ? "JUGADOR" : nombreJugador);
						guardado = true;
					}
				}
				else if (sobreBoton(rx, 660, rw, 55, puntoClic)) {
					if (!guardado) {
						guardarPuntaje(puntaje, nombreJugador.empty() ? "JUGADOR" : nombreJugador);
						guardado = true;
					}
					return esVictoria ? "siguiente" : "reintentar";
				}
				else if (sobreBoton(rx, 730, rw, 55, puntoClic)) {
					if (!guardado) {
						guardarPuntaje(puntaje, nombreJugador.empty() ? "JUGADOR" : nombreJugador);
						guardado = true;
					}
					return "salir";
				}
			}
		}

		EstadoJuego* estadoActual = replay.getEstadoActual();

		ventana.clear(COLOR_FONDO);
		dibujarFondo();

		dibujarTextoC(tituloFinal, centroX, 30, 48);
		dibujarTextoC("Puntaje Final: " + to_string(puntaje), centroX, 82, 22);

		dibujarTableroReplay(estadoActual, tabX, tabY, tamCelda);

		dibujarTexto("--- REPLAY DE PARTIDA ---", rx, 135, 20);
		int pasoIdx = replay.getIndiceActual();
		int totalPasos = replay.getTam();
		dibujarTexto("Paso: " + to_string(pasoIdx) + " / " + to_string(totalPasos), rx, 175, 22);

		if (estadoActual) {
			dibujarTexto("Puntos turno: " + to_string(estadoActual->getPuntaje()), rx, 212, 18);
			dibujarTexto("Lineas: " + to_string(estadoActual->getLineas()) + "  |  Nivel: " + to_string(estadoActual->getNivel()), rx, 238, 18);
		}

		dibujarBoton(rx, 305, mitadW, 42, "|<< INICIO", 18);
		dibujarBoton(rx + mitadW + 10, 305, mitadW, 42, "FINAL >>|", 18);
		dibujarBoton(rx, 355, mitadW, 42, "< ANTERIOR", 18);
		dibujarBoton(rx + mitadW + 10, 355, mitadW, 42, "SIGUIENTE >", 18);

		// Cuadro de texto para ingresar nombre
		dibujarTexto("REGISTRAR JUGADOR:", rx, 418, 18);

		sf::RectangleShape cajaNombre(sf::Vector2f(rw, 46.0f));
		cajaNombre.setPosition(rx, 448.0f);
		cajaNombre.setFillColor(sf::Color(8, 20, 38, 230));
		cajaNombre.setOutlineColor(COLOR_MARCO_NEON);
		cajaNombre.setOutlineThickness(2.0f);
		ventana.draw(cajaNombre);

		bool cursorVisible = ((int)(relojCursor.getElapsedTime().asSeconds() * 2.0f) % 2 == 0);
		if (nombreJugador.empty()) {
			dibujarTexto(cursorVisible ? "_" : "Escribe tu nombre...", rx + 14.0f, 460.0f, 18);
		} else {
			string textoConCursor = nombreJugador + (cursorVisible ? "_" : "");
			dibujarTexto(textoConCursor, rx + 14.0f, 460.0f, 18);
		}

		string textoBotonGuardar = guardado ? "¡REGISTRADO CON EXITO!" : "GUARDAR NOMBRE (ENTER)";
		dibujarBoton(rx, 505, rw, 42, textoBotonGuardar, 18);
		dibujarTexto("Se guardara en mejores_puntajes.txt", rx + 12.0f, 560, 14);

		dibujarBoton(rx, 660, rw, 55, textoAccion, 22);
		dibujarBoton(rx, 730, rw, 55, "MENU PRINCIPAL", 22);

		ventana.display();
	}

	if (!guardado) {
		guardarPuntaje(puntaje, nombreJugador.empty() ? "JUGADOR" : nombreJugador);
		guardado = true;
	}
	return "salir";
}

int interfazGrafica::jugarPartida(int nivelInicial, string& resultadoOut, Replay& replayOut) {
	Juego juego;
	juego.iniciar();
	juego.setNivel(nivelInicial);

	abrirVentana("TRON: Tetris Legacy");
	relojCaida.restart();
	bool pausado = false;
	tiempoPartidaSegundos = 0.0f;
	sf::Clock relojFrame;

	while (ventana.isOpen()) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) { 
				resultadoOut = "derrota"; 
				replayOut.transferirDesde(juego.getHistorial());
				return juego.getPuntaje(); 
			}
			else if (evento.type == sf::Event::KeyPressed){
				if (evento.key.code == sf::Keyboard::Escape) {
					pausado = !pausado;
					if (!pausado) {
						relojCaida.restart();
						relojFrame.restart();
					}
				} else if (!pausado) {
					manejarTeclado(juego, evento.key.code);
					if (juego.getCantLineasPorLimpiar() > 0) {
						animarLimpiezaLineas(juego);
						juego.completarLimpiezaLineas();
						relojCaida.restart();
					}
				}
			}
			else if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i puntoClic(evento.mouseButton.x, evento.mouseButton.y);
				float centroX = (float)ANCHO_VENTANA / 2.0f;
				float pausaX = centroX - 210.0f;
				float pausaY = (float)ALTO_VENTANA / 2.0f - 150.0f;

				if (pausado) {
					if (sobreBoton(pausaX + 35.0f, pausaY + 135.0f, 350.0f, 55.0f, puntoClic)) {
						pausado = false;
						relojCaida.restart();
						relojFrame.restart();
					}
					else if (sobreBoton(pausaX + 35.0f, pausaY + 210.0f, 350.0f, 55.0f, puntoClic)) {
						resultadoOut = "derrota";
						replayOut.transferirDesde(juego.getHistorial());
						return juego.getPuntaje();
					}
				} else {
					if (!juego.getGameOver() && !juego.getWin()) {
						float panelX = (float)(ORIGEN_TABLERO_X + ANCHO_TABLERO_PX + MARGEN);
						if (sobreBoton(panelX, 715, 200, 40, puntoClic)) {
							juego.deshacer();
							relojCaida.restart();
						} else if (sobreBoton(panelX, 765, 200, 40, puntoClic)) {
							juego.rehacer();
							relojCaida.restart();
						} else if (sobreBoton(panelX, 815, 200, 40, puntoClic)) {
							pausado = true;
						}
					}
				}
			}
		}

		float dt = relojFrame.restart().asSeconds();
		if (!pausado) {
			tiempoPartidaSegundos += dt;
			juego.actualizarEvento((int)tiempoPartidaSegundos);
			actualizarCaida(juego);
			if (juego.getCantLineasPorLimpiar() > 0) {
				animarLimpiezaLineas(juego);
				juego.completarLimpiezaLineas();
				relojCaida.restart();
			}
		}

		ventana.clear(COLOR_FONDO);
		dibujarFondo();
		dibujarTablero(juego);
		dibujarPiezaActual(juego);

		float centroTableroX = (float)ORIGEN_TABLERO_X + (float)ANCHO_TABLERO_PX / 2.0f;
		if (juego.getCaidaRapida()) {
			dibujarTextoC(">>> TURBO VELOCIDAD 2X <<<", centroTableroX, 16.0f, 18);
		} else if (juego.getDoblePuntos()) {
			dibujarTextoC(">>> PUNTOS DOBLES 2X <<<", centroTableroX, 16.0f, 18);
		} else if (juego.getBomba()) {
			dibujarTextoC(">>> BOMBA: LIMPIA FILAS <<<", centroTableroX, 16.0f, 18);
		}

		dibujarPanel(juego);

		if (pausado) {
			dibujarOverlayPausa();
		}

		ventana.display();

		if (juego.getWin() || juego.getGameOver()) {
			sf::Clock relojEspera;
			while (relojEspera.getElapsedTime().asSeconds() < 1.5f) {
				ventana.clear(COLOR_FONDO);
				dibujarFondo();
				dibujarTablero(juego);
				dibujarPiezaActual(juego);
				dibujarPanel(juego);
				ventana.display();
			}
			if(juego.getWin()){
				resultadoOut = "victoria";
			}else{
				resultadoOut = "derrota";	
			}
			replayOut.transferirDesde(juego.getHistorial());
			return juego.getPuntaje();
		}
	}
	resultadoOut = "derrota";
	replayOut.transferirDesde(juego.getHistorial());
	return juego.getPuntaje();
}

void interfazGrafica::dibujarPanel(Juego& juego) {
	float panelX = (float)(ORIGEN_TABLERO_X + ANCHO_TABLERO_PX + MARGEN);
	float panelY = (float)ORIGEN_TABLERO_Y;

	dibujarTexto("Puntos", panelX, panelY, 16); panelY += 20;
	dibujarTexto(to_string(juego.getPuntaje()), panelX, panelY, 20); 
	panelY += 30;

	dibujarTexto("Lineas", panelX, panelY, 16); panelY += 20;
	dibujarTexto(to_string(juego.getLineas()), panelX, panelY, 20);
	panelY += 30;

	dibujarTexto("Nivel", panelX, panelY, 16); panelY += 20;
	dibujarTexto(to_string(juego.getNivel()), panelX, panelY, 20);
	panelY += 30;

	dibujarTexto("Hold (C)", panelX, panelY, 16); panelY += 20;
	if (!juego.getHold().vacia()) {
		dibujarMiniPieza(juego.getHold().top(), panelX, panelY, 18);
	}
	panelY += 80;

	dibujarTexto("Siguiente", panelX, panelY, 16); panelY += 20;
	if (juego.getSiguiente()) {
		dibujarMiniPieza(juego.getSiguiente()->getTipo(), panelX, panelY, 18);
	}
	panelY += 80;

	TipoPieza* siguientesProximos = juego.getCola().proximas3();
	if (siguientesProximos) {
		dibujarTexto("Cola", panelX, panelY, 16); panelY += 20;
		for (int indice = 0; indice < 3; indice++) {
			dibujarMiniPieza(siguientesProximos[indice], panelX, panelY, 13);
			panelY += 46;
		}
		delete[] siguientesProximos;
	}

	if (juego.getGameOver()) {
		dibujarTexto("GAME OVER", panelX + 35.0f, 580.0f, 20);
	} else if (juego.getWin()) {
		dibujarTexto("VICTORIA", panelX + 45.0f, 580.0f, 20);
	}

	// Recuadro neon para el proximo evento
	float evBoxY = 635.0f;
	sf::RectangleShape marcoEv(sf::Vector2f(200.0f, 64.0f));
	marcoEv.setPosition(panelX, evBoxY);
	marcoEv.setFillColor(sf::Color(8, 22, 42, 220));
	marcoEv.setOutlineColor(COLOR_MARCO_NEON);
	marcoEv.setOutlineThickness(1.5f);
	ventana.draw(marcoEv);

	dibujarTexto("PROXIMO EVENTO", panelX + 12.0f, evBoxY + 8.0f, 13);
	string descEv = juego.proximoEvento();
	int segsEv = juego.duracionParaProximoEvento((int)tiempoPartidaSegundos);
	string txtEv = descEv + " (" + to_string(segsEv) + "s)";
	dibujarTexto(txtEv, panelX + 12.0f, evBoxY + 32.0f, 14);

	dibujarBoton(panelX, 715, 200, 40, "DESHACER (U)", 18);
	dibujarBoton(panelX, 765, 200, 40, "REHACER (R)", 18);
	dibujarBoton(panelX, 815, 200, 40, "PAUSA (ESC)", 18);
}

void interfazGrafica::animarLimpiezaLineas(Juego& juego) {
	sf::Clock relojAnim;
	while (ventana.isOpen() && relojAnim.getElapsedTime().asMilliseconds() < TIEMPO_ANIM_LINEA_MS) {
		sf::Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				ventana.close();
				return;
			}
		}

		float tiempoMs = (float)relojAnim.getElapsedTime().asMilliseconds();
		float progreso = tiempoMs / TIEMPO_ANIM_LINEA_MS;
		if (progreso > 1.0f) {
			progreso = 1.0f;
		}
		float anchoBlanco = progreso * (float)ANCHO_TABLERO_PX;

		ventana.clear(COLOR_FONDO);
		dibujarFondo();
		dibujarTablero(juego);
		dibujarPiezaActual(juego);
		dibujarPanel(juego);

		for (int i = 0; i < juego.getCantLineasPorLimpiar(); i++) {
			int fila = juego.getLineaPorLimpiar(i);
			float posY = (float)(ORIGEN_TABLERO_Y + fila * TAM_CELDA);
			sf::RectangleShape barraBrillo(sf::Vector2f(anchoBlanco, (float)TAM_CELDA));
			barraBrillo.setPosition((float)ORIGEN_TABLERO_X, posY);
			barraBrillo.setFillColor(sf::Color::White);
			barraBrillo.setOutlineColor(COLOR_MARCO_NEON);
			barraBrillo.setOutlineThickness(1.0f);
			ventana.draw(barraBrillo);
		}

		ventana.display();
	}
}

void interfazGrafica::dibujarOverlayPausa() {
	float centroX = (float)ANCHO_VENTANA / 2.0f;
	float anchoPausa = 420.0f;
	float altoPausa = 300.0f;
	float pausaX = centroX - anchoPausa / 2.0f;
	float pausaY = (float)ALTO_VENTANA / 2.0f - altoPausa / 2.0f;

	sf::RectangleShape veloPausa(sf::Vector2f((float)ANCHO_VENTANA, (float)ALTO_VENTANA));
	veloPausa.setPosition(0, 0);
	veloPausa.setFillColor(sf::Color(5, 8, 16, 210));
	ventana.draw(veloPausa);

	sf::RectangleShape marcoPausa(sf::Vector2f(anchoPausa, altoPausa));
	marcoPausa.setPosition(pausaX, pausaY);
	marcoPausa.setFillColor(sf::Color(8, 20, 38, 245));
	marcoPausa.setOutlineColor(COLOR_MARCO_NEON);
	marcoPausa.setOutlineThickness(2.0f);
	ventana.draw(marcoPausa);

	sf::RectangleShape barraTitulo(sf::Vector2f(anchoPausa, 48.0f));
	barraTitulo.setPosition(pausaX, pausaY);
	barraTitulo.setFillColor(sf::Color(0, 60, 90, 220));
	ventana.draw(barraTitulo);

	sf::RectangleShape lineaDivisoria(sf::Vector2f(anchoPausa, 2.0f));
	lineaDivisoria.setPosition(pausaX, pausaY + 48.0f);
	lineaDivisoria.setFillColor(COLOR_MARCO_NEON);
	ventana.draw(lineaDivisoria);

	dibujarTextoC("JUEGO EN PAUSA", centroX, pausaY + 12.0f, 22);
	dibujarTextoC("Presiona ESC para continuar", centroX, pausaY + 75.0f, 16);

	dibujarBoton(pausaX + 35.0f, pausaY + 135.0f, 350.0f, 55.0f, "REANUDAR", 20);
	dibujarBoton(pausaX + 35.0f, pausaY + 210.0f, 350.0f, 55.0f, "SALIR AL MENU", 20);
}

void interfazGrafica::manejarTeclado(Juego& juego, sf::Keyboard::Key tecla) {
	if (juego.getGameOver() || juego.getWin()){
		return;
	}
	if (!juego.getActual()){
		return;
	}
	switch (tecla) {
	case sf::Keyboard::Left:
		juego.moverIzquierda(); 
	break;
		case sf::Keyboard::Right: 
			juego.moverDerecha(); 
		break;
		case sf::Keyboard::Down: 
			juego.bajar(); relojCaida.restart(); 
			break;
		case sf::Keyboard::Up: 
			juego.rotarHorario(); 
		break;
		case sf::Keyboard::Z: 
			juego.rotarAntiHorario(); 
		break;
		case sf::Keyboard::Space: 
			juego.hardDrop(); relojCaida.restart(); 
			break;
		case sf::Keyboard::C: 
			juego.intercambiarHold(); 
		break;
		case sf::Keyboard::U: 
			juego.deshacer(); 
		break;
		case sf::Keyboard::R: 
			juego.rehacer(); 
		break;
		default: break;
	}
}

void interfazGrafica::actualizarCaida(Juego& juego) {
	if (juego.getGameOver() || juego.getWin()){
		return;
	}
	if (!juego.getActual()) {
		return;
	}
	float intervalo = juego.getTiempoCaida();
	if (relojCaida.getElapsedTime().asMilliseconds() >= intervalo) {
		juego.bajar();
		relojCaida.restart();
	}
}

void interfazGrafica::abrirVentana(string titulo) {
	if (ventana.isOpen()) ventana.close();
	ventana.create(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), titulo);
	ventana.setFramerateLimit(60);
}

int interfazGrafica::ejecutar() {
	fuenteOK = cargarFuente();
	fondoOK = cargarFondo();

	int nivelActual = 1;
	while (true) {
		int opcionMenu = mostrarMenu();
		if (opcionMenu == 0) {
			return 0;
		}
		string resultadoPartida;
		Replay replayPartida;
		int puntosPartida = jugarPartida(nivelActual, resultadoPartida, replayPartida);
		string accionFinal = mostrarPantallaFinal(resultadoPartida, puntosPartida, replayPartida);
		if (accionFinal == "salir") {
			continue;
		}
		if (accionFinal == "siguiente") {
			nivelActual++;
		}
	}
}
