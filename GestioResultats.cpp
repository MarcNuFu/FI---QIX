#include "GestioResultats.h"


/*void InicialitzarTaulaMillorJugadors(TipusJugador MillorsJugadors[])  //TOP 5 buit
{
	for (int i = 0; i < MAX_MILLORSJUGADORS; i++)
	{
		strcpy_s(MillorsJugadors[i].Nom, "--------------");
		MillorsJugadors[i].puntuacio = 0;
	}
}*/

void InicialitzarTaulaMillorJugadors(TipusJugador MillorsJugadors[])   //TOP 5 ple
{
	strcpy_s(MillorsJugadors[0].Nom, "QIX Master");
	MillorsJugadors[0].puntuacio = 1500;

	strcpy_s(MillorsJugadors[1].Nom, "Taito");
	MillorsJugadors[1].puntuacio = 1200;

	strcpy_s(MillorsJugadors[2].Nom, "Randy");
	MillorsJugadors[2].puntuacio = 1000;

	strcpy_s(MillorsJugadors[3].Nom, "Sandy");
	MillorsJugadors[3].puntuacio = 700;

	strcpy_s(MillorsJugadors[4].Nom, "Noob");
	MillorsJugadors[4].puntuacio = 1;
}

int ComprovarSiEsTop5(TipusJugador MillorsJugadors[], int punts)
{
	int i = 0;
	int trobat = 0;

	do
	{
		if (MillorsJugadors[i].puntuacio < punts)
		{
			trobat = 1;
		}

		i++;
	} while ((i < MAX_MILLORSJUGADORS) && (!trobat));

	if (trobat)
	{
		return (i - 1);
	}

	else
	{
		return -1;
	}
}

void DesplacarArray(TipusJugador MillorsJugadors[], int posicio)
{
	for (int i = MAX_MILLORSJUGADORS - 1; i > posicio; i--)
	{
		strcpy_s(MillorsJugadors[i].Nom, MillorsJugadors[i - 1].Nom);
		MillorsJugadors[i].puntuacio = MillorsJugadors[i - 1].puntuacio;
	}
}

void EmplenarPosicioTaula(TipusJugador &PosicioAOmplir, int punts, HANDLE hScreen)
{
	TextColor(LIGHTGREY, BLACK, hScreen);
	cout << "Entra el teu nom: " << endl;
	cin >> PosicioAOmplir.Nom;
	(PosicioAOmplir).puntuacio = punts;
}

void EscriuRanking(TipusJugador MillorsJugadors[], HANDLE hScreen)
{
	TextColor(LIGHTRED, BLACK, hScreen);
	cout << "---------- Millors puntuacions ----------" << endl << endl;

	TextColor(LIGHTGREY, BLACK, hScreen);
	for (int i = 0; i < MAX_MILLORSJUGADORS; i++)
	{
		cout << i + 1 << ".- " << MillorsJugadors[i].Nom;

		GotoXY(22, 2 + i, hScreen);
		cout << MillorsJugadors[i].puntuacio << endl;
	}

	TextColor(LIGHTRED, BLACK, hScreen);
	cout << endl << "-----------------------------------------" << endl;
}