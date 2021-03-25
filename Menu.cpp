#include "Menu.h"

void MenuPrincipal(HANDLE hScreen)  //Imprimir el menu
{
	TextColor(LIGHTRED, BLACK, hScreen);
	cout << "------------- Menu Principal ------------" << endl << endl;

	TextColor(LIGHTGREY, BLACK, hScreen);
	cout << "1. Jugar" << endl;
	cout << "2. Configurar" << endl;
	cout << "3. Millors puntuacions" << endl;
	cout << "4. Sortir" << endl;

	TextColor(LIGHTRED, BLACK, hScreen);
	cout << endl << "-----------------------------------------" << endl;
}

void MenuNivellDificultat(HANDLE hScreen)
{
	TextColor(LIGHTRED, BLACK, hScreen);
	cout << "-------------Menu Dificultat-------------" << endl << endl;

	TextColor(LIGHTGREY, BLACK, hScreen);
	cout << "1.-Principiant" << endl;
	cout << "2.-Intermedi" << endl;
	cout << "3.-Avancat" << endl;

	TextColor(LIGHTRED, BLACK, hScreen);
	cout << endl << "-----------------------------------------" << endl;

	TextColor(LIGHTGREY, BLACK, hScreen);
}

void LogoQIX(HANDLE hScreen)
{
	//Dibuixar Q
	TextColor(LIGHTBLUE, BLACK, hScreen);

	GotoXY(17, 10, hScreen);
	cout << char(MUR) << char(MUR) << char(MUR) << char(MUR);

	GotoXY(15, 11, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(15, 12, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(15, 13, hScreen);
	cout << char(MUR) << char(MUR);

	GotoXY(21, 11, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(21, 12, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(21, 13, hScreen);
	cout << char(MUR) << char(MUR);

	GotoXY(17, 14, hScreen);
	cout << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR);

	//Dibuixar I
	TextColor(LIGHTBLUE, BLACK, hScreen);

	GotoXY(17, 16, hScreen);
	cout << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR);

	GotoXY(19, 17, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(19, 18, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(19, 19, hScreen);
	cout << char(MUR) << char(MUR);

	GotoXY(17, 20, hScreen);
	cout << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR) << char(MUR);

	//Dibuixar X
	TextColor(LIGHTBLUE, BLACK, hScreen);

	GotoXY(15, 22, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(15, 26, hScreen);
	cout << char(MUR) << char(MUR);

	GotoXY(17, 23, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(17, 25, hScreen);
	cout << char(MUR) << char(MUR);

	GotoXY(19, 24, hScreen);
	cout << char(MUR) << char(MUR);

	GotoXY(21, 23, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(21, 25, hScreen);
	cout << char(MUR) << char(MUR);

	GotoXY(23, 22, hScreen);
	cout << char(MUR) << char(MUR);
	GotoXY(23, 26, hScreen);
	cout << char(MUR) << char(MUR);
}