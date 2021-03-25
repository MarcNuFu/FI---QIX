#include <iostream>
#include "Graphics_Console.h"

using namespace std;

#define MAX_MILLORSJUGADORS 5

#define MUR 219 // Codi simbol MUR

typedef struct  //Estructura per a jugadors
{
	char Nom[15];
	int puntuacio;
}TipusJugador;


void InicialitzarTaulaMillorJugadors(TipusJugador MillorsJugadors[]);  //Procediment per a inicialitzar ranking

int ComprovarSiEsTop5(TipusJugador MillorsJugadors[], int punts); //Funcio per a comprovar si és un millor jugador

void DesplacarArray(TipusJugador MillorsJugadors[], int posicio);  //Procediment per a incloure un nou millor jugador

void EmplenarPosicioTaula(TipusJugador &PosicioAOmplir, int punts, HANDLE hScreen);  //Procediment per a introduir dades d'un nou millor jugador

void EscriuRanking(TipusJugador MillorsJugadors[], HANDLE hScreen);  //Procediment per a imprimir els millors jugadors