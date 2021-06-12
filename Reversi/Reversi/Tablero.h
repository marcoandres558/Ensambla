#pragma once
#define DEBUG
#include <assert.h>	/*Para usar assert*/
#include <iostream>
#include <sstream>
using namespace std;

class Tablero
{
public:
	enum Ficha { nula, blanca, negra };

	int casillasDisponibles = 63;

	//EFE: Crea un tablero de reversi en posición incial.
	Tablero();

	/*Metodos observadores publicos*/

	//REQ: (0 <= f, c <=7) && (color == blanca || color == negra).
	//EFE: retorna true si la jugada en [f,c] es valida para las fichas del color,
	//	   retorna false en caso contrario.
	bool validarJugada(int f, int c, Ficha color) const;

	//EFE: retorna true si el estado actual es un estado final del juego,
	// retorna false en caso contrario.
	bool verFin() const;

	//REQ: color == blanca || color == negra.
	//EFE: retorna true si las de color no tienen opción para jugar,
	//	   false en caso contrario.
	bool verPasan(Ficha color) const;

	//REQ: 0 <= f,c <= 7.
	//EFE: retorna el valor en la fila f columna c.
	Ficha verFichaEn(int f, int c) const;

	//REQ: (0 <= f,c <= 7).
	//MOD: *this.
	//EFE: coloca en [f,c] la ficha de color.
	void colocarSimple(int f, int c, Ficha color);

	/* Métodos modificadores*/
	//REQ: (0 <= f,c <= 7) && (validarJugada(f,c,color) == true) && (color == blanca || color == negra).
	//MOD: *this.
	//EFE: coloca en [f,c] la ficha de color lo que implica realizar todos los flanqueos correspondientes
	void colocarFlanqueando(int f, int c, Ficha color);

	string toString() const;

	void pideJugada(const Tablero& tr, string nombre, Tablero::Ficha color, int& f, int& c);



	//private:
		/* Métodos observadores de flanqueo privados, se invocarán desde "validarJugada()" */

		//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra).
		//EFE: retorna true si color sí flanquea la fila f, desde [f,c]; false en caso contrario.
	bool verFlanqueaFila(int f, int c, Ficha color) const;

	//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra).
	//EFE: retorna true si color sí flanquea la columna c, desde [f,c]; false en caso contrario.
	bool verFlanqueaColumna(int f, int c, Ficha color) const;

	//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra).
	//EFE: retorna true si color sí flanquea la diagonal ascendente <f,c>, desde [f,c]; false en caso contrario.
	bool verFlanqueaDiagonalAscendente(int f, int c, Ficha color) const;

	//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra).
	//EFE: retorna true si color sí flanquea la diagonal descendente <f,c>, desde [f,c]; false en caso contrario.
	bool verFlanqueaDiagonalDescendente(int f, int c, Ficha color) const;

	/* Métodos modificadores de flanqueo privados, se invocarán desde "colocar()" */
	//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra) && verFlanqueaFila(f,c).
	//MOD: *this.
	//EFE: flanquea la fila f, desde [f,c].
	void flanqueaFila(int f, int c, Ficha color);

	//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra) && verFlanqueaColumna(f,c).
	//MOD: *this.
	//EFE: flanquea la columna c, desde [f,c].
	void flanqueaColumna(int f, int c, Ficha color);

	//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra) && verFlanqueaDiagonalAscendente(f,c).
	//MOD: *this.
	//EFE: flanquea la diagonal ascendente <f,c>, desde [f,c].
	void flanqueaDiagonalAscendente(int f, int c, Ficha color);

	//REQ: (0 <= f,c <= 7) && (color == blanca || color == negra) && verFlanqueaDiagonalDescendente(f,c).
	//MOD: *this.
	//EFE: flanquea la diagonal descendente <f,c>, desde [f,c].
	void flanqueaDiagonalDescendente(int f, int c, Ficha color);

	/* REPRESENTACIÓN DEL TABLERO */
	Ficha tablero[8][8];
};

Tablero::Tablero()
{
	for (int f = 0; f < 8; f++)
		for (int c = 0; c < 8; c++)
			tablero[f][c] = nula;

	colocarSimple(3, 3, blanca);
	colocarSimple(4, 4, blanca);
	colocarSimple(4, 3, negra);
	colocarSimple(3, 4, negra);
}
bool Tablero::validarJugada(int f, int c, Ficha color) const
{
	bool resultado = false;
	if (verFlanqueaFila(f, c, color) || verFlanqueaColumna(f, c, color) || verFlanqueaDiagonalAscendente(f, c, color) ||
		verFlanqueaDiagonalDescendente(f, c, color))
		resultado = true;
	return resultado;
}
bool Tablero::verFin() const
{
	cout << casillasDisponibles << endl;
	if (casillasDisponibles >= 0)
		return false;
	else
	{
		cout << "Fin del juego" << endl;
		return true;
	}
	return true;
}
bool Tablero::verPasan(Ficha color) const
{
	return false;
}
Tablero::Ficha Tablero::verFichaEn(int f, int c) const
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	return tablero[f][c];
}
void Tablero::colocarSimple(int f, int c, Ficha color)
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	if (!verFin())
	{
		casillasDisponibles--;
		tablero[f][c] = color;
	}
	verFin();
}
void Tablero::colocarFlanqueando(int f, int c, Ficha color)
{
}
bool Tablero::verFlanqueaFila(int f, int c, Ficha color) const
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (f <= 7));
	assert(color != nula);

	bool resultado = false;
	bool encuentraColor = false;
	bool encuentraOtroColor = false;
	Ficha otroColor;

	//Determina cual es el otro color.
	if (color == negra)
		otroColor = blanca;
	else otroColor = negra;

	//Busca hacia la izquierda: de c-1 a 0.
	int cc = c - 1;
	while ((cc >= 0) && (tablero[f][cc] == otroColor))
	{
		encuentraOtroColor = true;
		cc--;
	}

	if (cc >= 0 && tablero[f][cc] != nula)
		encuentraColor = true;

	//Determina si debe buscar a la derecha.
	if (encuentraColor && encuentraOtroColor)
		resultado = true;
	else
	{
		encuentraColor = false;
		encuentraOtroColor = false;
		//Busca hacia la derecha: de c+1 a 7.
		cc = c + 1;
		while ((cc < 8) && (tablero[f][cc] == otroColor))
		{
			encuentraOtroColor = true;
			cc++;
		}
		if (cc < 8 && tablero[f][cc] != nula)
			encuentraColor = true;
		if (encuentraColor && encuentraOtroColor)
			resultado = true;
	}
	return resultado;
}
bool Tablero::verFlanqueaColumna(int f, int c, Ficha color) const
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (f <= 7));
	assert(color != nula);

	bool resultado = false;
	bool encuentraColor = false;
	bool encuentraOtroColor = false;
	Ficha otroColor;

	//Determina cual es el otro color.
	if (color == negra)
		otroColor = blanca;
	else otroColor = negra;

	//Busca hacia la arriba: de f-1 a 0.
	int ff = f - 1;
	while ((ff >= 0) && (tablero[ff][c] == otroColor))
	{
		encuentraOtroColor = true;
		ff--;
	}

	if (ff >= 0 && tablero[ff][c] != nula)
		encuentraColor = true;

	//Determina si debe buscar hacia abajo.
	if (encuentraColor && encuentraOtroColor)
		resultado = true;
	else
	{
		encuentraColor = false;
		encuentraOtroColor = false;
		//Busca hacia abajo: de f+1 a 7.
		ff = f + 1;
		while ((ff < 8) && (tablero[ff][c] == otroColor))
		{
			encuentraOtroColor = true;
			ff++;
		}
		if (ff < 8 && tablero[ff][c] != nula)
			encuentraColor = true;
		if (encuentraColor && encuentraOtroColor)
			resultado = true;
	}
	return resultado;
}
bool Tablero::verFlanqueaDiagonalAscendente(int f, int c, Ficha color) const
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	assert(color != nula);

	bool resultado = false;
	bool encuentra_color = false;
	bool encuentra_otro_color = false;
	Ficha otro_color;

	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;

	// busca hacia arriba desde [f,c] hacia la posición más alta de la diagonal ascendente
	int ff = f - 1;
	int cc = c + 1;
	while ((ff > 0) && (cc < 8) && (tablero[ff][cc] == otro_color))
	{
		encuentra_otro_color = true;
		ff--; cc++;
	}
	if ((ff >= 0) && (cc < 8) && tablero[ff][cc] != nula)
		encuentra_color = true;

	// determina si debe buscar hacia abajo, desde [f,c] hasta la posición más baja de la diagonal ascendente
	if (encuentra_color && encuentra_otro_color)
		resultado = true;
	else {
		ff = f + 1;
		cc = c - 1;
		encuentra_color = false;
		encuentra_otro_color = false;
		while ((ff < 8) && (cc > 0) && (tablero[ff][cc] == otro_color))
		{
			encuentra_otro_color = true;
			ff++; cc--;
		}
		if ((ff < 8) && (cc >= 0) && tablero[ff][cc] != nula)
			encuentra_color = true;
		if (encuentra_color && encuentra_otro_color)
			resultado = true;
	}
	return resultado;
}
bool Tablero::verFlanqueaDiagonalDescendente(int f, int c, Ficha color) const
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	assert(color != nula);

	bool resultado = false;
	bool encuentra_color = false;
	bool encuentra_otro_color = false;
	Ficha otro_color;

	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;

	// busca hacia abajo desde [f,c] hacia la posición más baja de la diagonal descendente.
	int ff = f + 1;
	int cc = c + 1;
	while ((ff < 8) && (cc < 8) && (tablero[ff][cc] == otro_color))
	{
		encuentra_otro_color = true;
		ff++; cc++;
	}
	if ((ff < 8) && (cc < 8) && tablero[ff][cc] != nula)
		encuentra_color = true;

	// determina si debe buscar hacia arriba, desde [f,c] hasta la posición más alta de la diagonal descendente
	if (encuentra_color && encuentra_otro_color)
		resultado = true;
	else {
		ff = f - 1;
		cc = c - 1;
		encuentra_color = false;
		encuentra_otro_color = false;
		while ((ff > 0) && (cc > 0) && (tablero[ff][cc] == otro_color))
		{
			encuentra_otro_color = true;
			ff--; cc--;
		}
		if ((ff >= 0) && (cc >= 0) && tablero[ff][cc] != nula)
			encuentra_color = true;
		if (encuentra_color && encuentra_otro_color)
			resultado = true;
	}
	return resultado;
}
void Tablero::flanqueaFila(int f, int c, Tablero::Ficha color)
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	assert(color != nula);
	assert(verFlanqueaFila(f, c, color));
	Ficha otro_color;
	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;
	// flanquea hacia la izquierda: de c-1 a 0
	int cc = c - 1;
	while ((cc >= 0) && (tablero[f][cc] == otro_color))
	{
		tablero[f][cc] = color;
		cc--;
	}
	// flanquea hacia la derecha: de c+1 a 7
	cc = c + 1;
	while ((cc < 8) && (tablero[f][cc] == otro_color))
	{
		tablero[f][cc] = color;
		cc++;
	}
}

void Tablero::flanqueaColumna(int f, int c, Tablero::Ficha color)
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	assert(color != nula);
	assert(verFlanqueaColumna(f, c, color));
	Ficha otro_color;
	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;
	// flanquea hacia abajo: de c-1 a 0
	int ff = f- 1;
	while ((ff>= 0) && (tablero[ff][c] == otro_color))
	{
		tablero[ff][c] = color;
		ff--;
	}
	// flanquea hacia arriba: de c+1 a 7
	ff = f + 1;
	while ((ff < 8) && (tablero[ff][c] == otro_color))
	{
		tablero[ff][c] = color;
		ff++;
	}
}

void Tablero::flanqueaDiagonalAscendente(int f, int c, Tablero::Ficha color)
{

	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	assert(color != nula);
	assert(verFlanqueaDiagonalAscendente(f, c, color));

	Ficha otro_color;

	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;

	// busca hacia arriba desde [f,c] hacia la posición más alta de la diagonal ascendente
	int ff = f - 1;
	int cc = c + 1;
	while ((ff > 0) && (cc < 8) && (tablero[ff][cc] == otro_color))
	{
		tablero[ff][cc] == color;
		ff--; cc++;
	}

	ff = f + 1;
	cc = c - 1;
	// determina si debe buscar hacia abajo, desde [f,c] hasta la posición más baja de la diagonal ascendente
	while ((ff < 8) && (cc > 0) && (tablero[ff][cc] == otro_color))
	{
		tablero[ff][cc] = color;
		ff++; cc--;
	}
}

void Tablero::flanqueaDiagonalDescendente(int f, int c, Tablero::Ficha color)
{
	assert((0 <= f) && (f <= 7));
	assert((0 <= c) && (c <= 7));
	assert(color != nula);
	assert(verFlanqueaDiagonalDescendente(f, c, color));

	Ficha otro_color;

	// determina cuál es el otro color
	if (color == negra)
		otro_color = blanca;
	else otro_color = negra;

	// busca hacia abajo desde [f,c] hacia la posición más baja de la diagonal descendente.
	int ff = f + 1;
	int cc = c + 1;
	while ((ff < 8) && (cc < 8) && (tablero[ff][cc] == otro_color))
	{
		tablero[ff][cc] = color;
		ff++; cc++;
	}
	ff = f - 1;
	cc = c - 1;
	while ((ff > 0) && (cc > 0) && (tablero[ff][cc] == otro_color))
	{
		tablero[ff][cc] = color;
		ff--; cc--;
	}
}

string Tablero::toString() const
{
	string separador = " +---+---+---+---+---+---+---+---+";
	string numeros_fila = " 0 1 2 3 4 5 6 7";
	ostringstream salida; // es un buffer de memoria con caracteres listos para ser desplegados por consola
	salida << numeros_fila << endl;
	salida << separador << endl;
	for (int f = 0; f < 8; f++)
	{
		salida << f << " |";
		for (int c = 0; c < 8; c++)
		{
			if (tablero[f][c] != nula)
			{
				salida << ((tablero[f][c] == negra) ? " N" : " B");
			}
			else salida << " ";
			salida << " |";
		}
		salida << endl;
		salida << separador << endl;
	}
	return salida.str(); // se accede el contenido del buffer y se retorna como hilera
}

void pideJugada(const Tablero& tr, string nombre, Tablero::Ficha color, int& f, int& c)
{
	bool validez = false;
	while ((f > 7) || (f < 0) || (c > 7) || (c < 0) || !validez)
	{
		cout << nombre << " por favor digite la fila de su jugada: "; cin >> f;
		cout << nombre << " por favor digite la columna de su jugada: "; cin >> c;
		cout << endl;
		validez = tr.validarJugada(f, c, color);
		if (!validez)
			cout << nombre << ": SU JUGADA NO ES VALIDA!" << endl;
	}
}