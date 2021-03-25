#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "Graphics_Console.h"
#include "Menu.h"
#include "Joc.h"
#include "GestioResultats.h"

using namespace std;


int main()
{
	HANDLE hScreen;                                 //Declaració de variable per a modificar el tamany de la pantalla i la seva utilització
	hScreen = GetStdHandle(STD_OUTPUT_HANDLE);
	InitScreen(hScreen);

	TipusJugador MillorsJugadors[MAX_MILLORSJUGADORS];
	int dificultat = 1;
	int punts = 0;
	int posicio = -1;
	unsigned char tecla = 0;

	InicialitzarTaulaMillorJugadors(MillorsJugadors);

	do
	{
		system("cls");  //Esborrem pantalla
		MenuPrincipal(hScreen);  //Escriure el menu
		LogoQIX(hScreen);  //Dibuixem el logo de QIX
		tecla = _getch();  //Rebre la tecla premuda

		switch (tecla)  //Selecció en el menu
		{
		case JUGAR:   //Iniciem el joc
			system("cls");
			punts = Joc(dificultat);
			system("cls");
			posicio = ComprovarSiEsTop5(MillorsJugadors, punts);
			if (posicio >= 0 && posicio <= 5)
			{
				DesplacarArray(MillorsJugadors, posicio);
				EmplenarPosicioTaula(MillorsJugadors[posicio], punts, hScreen);
			}
			break;

		case CONFIGURAR:    //Iniciem la configuració
			do
			{
				system("cls");
				MenuNivellDificultat(hScreen);
				cin >> dificultat;
			} while (dificultat < 1 || dificultat > 3);

			break;

		case PUNTUACIO:   //Mostrem puntuació
			system("cls");
			EscriuRanking(MillorsJugadors, hScreen);
			_getch();
			break;

		case SORTIR:    //Sortim de l'aplicació
			system("cls");
			break;

		default:     
			system("cls");
			break;
		}
	} while (tecla != SORTIR);


	_getch();
	return 0;
}

