#include <stdio.h>
#include <iostream>
#include "Graphics_Console.h"

using namespace std;

//=====================================================================
//Constants per al menu
#define JUGAR '1'
#define CONFIGURAR '2'
#define PUNTUACIO '3'
#define SORTIR '4'

//=====================================================================
// Codi del simbol utilitzat com a bloc de disseny de les parets del camp de joc
#define MUR 219 // Codi simbol MUR




void MenuPrincipal(HANDLE hScreen);  //Procediment per a imprimir el menu principal

void MenuNivellDificultat(HANDLE hScreen); //Procediment per a imprimir el menu de nivell de difucltat

void LogoQIX(HANDLE hScreen); //Procediment per a dibuixar logo QIX
