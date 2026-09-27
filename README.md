# 🕹️ Tetris TRON - Proyecto 1

![C++](https://img.shields.io/badge/Lenguaje-C%2B%2B11-blue.svg)
![SFML](https://img.shields.io/badge/Librer%C3%ADa-SFML%202.5.1-brightgreen.svg)
![IDE](https://img.shields.io/badge/IDE-ZinjaI-orange.svg)
![Curso](https://img.shields.io/badge/Curso-Estructuras%20de%20Datos%20(EIF207)-red.svg)
![Universidad](https://img.shields.io/badge/UNA-Campus%20P%C3%A9rez%20Zeled%C3%B3n-darkblue.svg)

---

## 📋 Información Académica

| Campo | Detalle |
| :--- | :--- |
| **Institución** | Universidad Nacional de Costa Rica (UNA) |
| **Sede** | Sede Regional Brunca, Campus Pérez Zeledón |
| **Curso** | Estructuras de Datos (EIF207) |
| **Estudiante** | Oscar Salas Fallas |
| **Identificación** | 119440628 |
| **Correo Institucional** | oscar.salas.fallas@est.una.ac.cr |
| **Ciclo Lectivo** | Ciclo II 2026 |

---

## 🎮 Descripción del Proyecto

**Tetris TRON** es una recreación avanzada del legendario juego de bloques arcade, ambientada con una temática retro-futurista inspirada en la película *TRON* (luces neón cian, magenta, amarillo y azul eléctrico).

El proyecto fue desarrollado desde cero en **C++** como parte de la cátedra de Estructuras de Datos. Con el fin de aplicar directamente los conceptos de gestión de memoria dinámica y manipulación de punteros, **no se utilizaron contenedores de la biblioteca estándar (STL)** para la lógica medular. En su lugar, se implementaron estructuras dinámicas propias (listas enlazadas simples y dobles, colas FIFO, colas de prioridad y pilas LIFO), así como algoritmos clásicos de ordenamiento.

---

## 🏗️ Arquitectura y Estructuras de Datos

A continuación se detallan las estructuras de datos desarrolladas manualmente para cumplir con los requerimientos del sistema:

| Estructura / Clase | Tipo de Estructura | Función y Aplicación en el Juego |
| :--- | :--- | :--- |
| **`ColaPiezas`** | **Cola FIFO** (First-In, First-Out) | Gestiona la secuencia de tetrominós venideros mediante el generador oficial de 7 bolsas (*7-bag randomizer*), garantizando una distribución equitativa de piezas en la previsualización (`Next`). |
| **`PilaHold`** | **Pila LIFO** (Last-In, First-Out) | Permite al jugador reservar la pieza activa actual (`Hold`) con capacidad unitaria. Intercambia la pieza retenida con la activa y previene intercambios múltiples en un mismo turno. |
| **`Tablero`** | **Lista Enlazada Simple** | Representa la matriz de 20 filas por 10 columnas como una lista enlazada de nodos `NodoFila`. Facilita la detección, eliminación y liberación en memoria de filas completas, insertando nuevas filas vacías al inicio. |
| **`ColaEventos`** | **Cola de Prioridad** (por tiempo) | Administra los eventos temporizados y aleatorios del juego ordenados por su marca temporal (*timestamp*). Controla efectos dinámicos como *Turbo Velocidad*, *Doble Puntaje* y la *Bomba Limpia-Filas*. |
| **`Replay`** | **Lista Doblemente Enlazada** | Almacena los estados históricos de la partida (`NodoEstado`) con enlaces bidireccionales (`anterior` y `siguiente`). Hace posible el sistema ilimitado de **Deshacer** (*Undo*) y **Rehacer** (*Redo*), así como la reproducción interactiva post-partida. |
| **`Puntaje`** | **Persistencia y Algoritmos de Ordenamiento** | Lee y almacena el archivo plano `mejores_puntajes.txt`. Implementa de forma manual los algoritmos de ordenamiento **Selection Sort** y **Merge Sort** para clasificar el salón de la fama. |
| **`Juego` & `interfazGrafica`** | **Arquitectura Desacoplada** | Separación clara entre el núcleo de lógica, reglas, colisiones y eventos (`Juego`), y el subsistema de renderizado gráfico por hardware en SFML con animaciones y efectos neón (`interfazGrafica`). |

---

## 💻 Entorno de Desarrollo y Librerías

El sistema fue programado en el entorno de desarrollo integrado **ZinjaI** utilizando el compilador **MinGW / GCC** con soporte para el estándar **C++11** o superior, integrando la biblioteca multimedia **SFML 2.5.1**.

Tanto el compilador como la biblioteca gráfica están disponibles como complementos empaquetados (`.zcp`) en la página oficial del IDE:
* 🌐 **Descarga de complementos ZinjaI:** [https://zinjai.sourceforge.net/index.php?page=downextras.php](https://zinjai.sourceforge.net/index.php?page=downextras.php)

> [!NOTE]
> Para mayor comodidad, los paquetes instaladores oficiales ya se encuentran incluidos en la raíz de este repositorio:
> - `zinjai-add-mingw64-gcc7-win-20180222.zcp` (Compilador MinGW-w64 GCC 7)
> - `zinjai-add-sfml2-w64-20180222.zcp` (Librería SFML 2.5.1 para MinGW-w64)

---

## ⚙️ Instrucciones de Compilación y Ejecución

Siga estos pasos para compilar y ejecutar el proyecto en ZinjaI:

### 1. Instalación de Complementos (MinGW y SFML)
1. Abra el IDE **ZinjaI**.
2. Vaya al menú superior: **Herramientas (Tools)** $\rightarrow$ **Instalar complementos...**
3. Haga clic en el botón **Instalar...**
4. En el explorador de archivos, seleccione el archivo `zinjai-add-mingw64-gcc7-win-20180222.zcp` y complete el asistente.
5. Repita el proceso anterior para instalar el archivo `zinjai-add-sfml2-w64-20180222.zcp`.
6. Reinicie ZinjaI si el programa lo solicita para cargar los perfiles de compilador y librerías.

### 2. Apertura del Proyecto
1. En ZinjaI, seleccione **Archivo** $\rightarrow$ **Abrir Proyecto...**
2. Navegue a la carpeta `Tetris_OscarSalasFallas/` y abra el archivo de proyecto:
   ```
   Tetris_OscarSalasFallas.zpr
   ```

### 3. Verificación de Recursos
> [!IMPORTANT]
> Es indispensable mantener la carpeta `resources/` (fuentes tipográficas, texturas e imágenes) dentro de la carpeta del proyecto ejecutable para evitar fallos de inicialización o excepciones durante la carga de assets gráficos.

### 4. Compilación y Ejecución
- Presione la tecla **`F9`** (o vaya a **Ejecutar** $\rightarrow$ **Compilar y Ejecutar**).
- El proyecto se compilará de forma automática enlazando las librerías dinámicas de SFML y desplegará la ventana principal de juego en resolución 1000x800 píxeles.

---

## ⌨️ Guía de Controles del Juego

### 🕹️ Durante la Partida

| Acción | Control / Tecla | Descripción |
| :--- | :---: | :--- |
| **Mover a la Izquierda** | <kbd>←</kbd> | Desplaza la pieza activa una columna a la izquierda. |
| **Mover a la Derecha** | <kbd>→</kbd> | Desplaza la pieza activa una columna a la derecha. |
| **Caída Suave (Soft Drop)** | <kbd>↓</kbd> | Aumenta la velocidad de descenso de la pieza activa. |
| **Rotación Horaria** | <kbd>↑</kbd> | Gira la pieza $90^\circ$ en sentido de las agujas del reloj. |
| **Rotación Antihoraria** | <kbd>Z</kbd> | Gira la pieza $90^\circ$ en sentido inverso a las agujas del reloj. |
| **Caída Instantánea (Hard Drop)** | <kbd>Espacio</kbd> | Fija la pieza instantáneamente en el fondo y genera puntuación adicional. |
| **Guardar en Reserva (Hold)** | <kbd>C</kbd> | Guarda la pieza en espera o la intercambia con la actual. |
| **Deshacer Movimiento (Undo)** | <kbd>U</kbd> | Revierte el estado del juego al movimiento anterior. |
| **Rehacer Movimiento (Redo)** | <kbd>R</kbd> | Restaura el estado previamente revertido. |
| **Pausar / Menú** | <kbd>ESC</kbd> | Pausa la partida o reanuda el juego actual. |

---

### 📼 Pantalla Final y Modo Replay

| Acción | Control / Interfaz | Descripción |
| :--- | :---: | :--- |
| **Registro de Récord** | Cuadro de texto + <kbd>Enter</kbd> | Permite escribir el nombre del jugador tras un Game Over o Victoria y confirmarlo con `Enter` para guardarlo en los puntajes máximos. |
| **Navegación de Replay** | <kbd>←</kbd> / <kbd>→</kbd> | Retrocede o avanza paso a paso entre los fotogramas grabados de la partida. |
| **Controles en Pantalla** | Clic en Botones UI | Botones gráficos para saltar al inicio, reproducir/pausar automáticamente (`Play/Pause`), avanzar, retroceder y salir al menú principal. |


---

## 📜 Licencia y Créditos

Proyecto desarrollado con fines académicos para la carrera de **Ingeniería en Sistemas de Información** de la **Universidad Nacional de Costa Rica**.
Todos los derechos reservados © 2026.
