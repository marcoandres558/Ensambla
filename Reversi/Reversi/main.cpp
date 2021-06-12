//By: Marco Rodriguez B96632, Rodrigo Mendoza C04813
#include <iostream>
using namespace std;
#include "Tablero.h"
int main()
{
	Tablero tr;
	string nombre_negras = "";
	string nombre_blancas = "";
	while (nombre_negras == "")
	{
		cout << "Digite el nombre quien juega las NEGRAS: ";
		cin >> nombre_negras;
	}
	while (nombre_blancas == "")
	{
		cout << "Digite el nombre quien juega las BLANCAS: ";
		cin >> nombre_blancas;
	}
	cout << tr.toString() << endl << endl;
	while (!tr.verFin())
	{
		int f, c = 0;
		pideJugada(tr, nombre_negras, Tablero::negra, f, c);
		tr.colocarFlanqueando(f, c, Tablero::negra);
		cout << tr.toString() << endl << endl;
		pideJugada(tr, nombre_blancas, Tablero::blanca, f, c);
		tr.colocarFlanqueando(f, c, Tablero::blanca);
		cout << tr.toString() << endl << endl;
	}
	return 0;
}
