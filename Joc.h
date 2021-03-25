#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Graphics_Console.h"

using namespace std;

//=====================================================================
// Definició de tecles amb el seu valor ASCII
#define TECLA_ESC 27
#define TECLA_ESTESA 224

#define TECLA_ESQUERRA 75
#define TECLA_DRETA 77
#define TECLA_ADALT 72
#define TECLA_ABAIX 80

//=====================================================================
// Inici del taulell respecte la cantonada superior esquerra
#define INICI_X 4
#define INICI_Y 5

//=====================================================================
// Fi del taulell respecte la cantonada superior esquerra
#define FI_X 36
#define FI_Y 25

//=====================================================================
// Codi del simbol utilitzat com a bloc de disseny de les parets del camp de joc
#define MUR 219 // Codi simbol MUR

//=====================================================================
// Definició del moviment del STIX  
#define MOV_PARAT 0
#define MOV_DRETA 2
#define MOV_ESQUERRA 4
#define MOV_ADALT 1
#define MOV_ABAIX 3

//=====================================================================
// Definició de l'area del tauler
#define AREARECTANGLE (FI_X-INICI_X)*(FI_Y-INICI_Y)  

//=====================================================================
// "Velocitat" per al QIX
#define VELOCITATPC 7000  //"Velocitat" per al QIX, quant més grans sigui aquest valor més lent anirà el QIX



int Joc(int nivell);    //Procediment del Joc 
void Taulell(HANDLE hScreen);//Procediment per a pintar el taulell
void InfoPuntsPartida(int punts, HANDLE hScreen); //Procediment per a escriure els punts
void InfoVidesPartida(int vides, HANDLE hScreen);  //Procediment per a escriure les vides
void InfoNivellPartida(int nivell, HANDLE hScreen);  //Procediment per a escriure els nivells

void PintarQIX(int qixX, int qixY, int color, HANDLE hScreen); //Procediment per a pintar el QIX
void PintarCursor(int cursorX, int cursorY, HANDLE hScreen); //Procediment per a pintar el cursor

void GameOver(HANDLE hScreen); //Procediment per a escriure "GAME OVER"

void PintarObjecte(int X, int Y, char Obj, int ColorObj, HANDLE hScreen); //Procediment per a pintar objectes
void EsborrarObjecte(int X, int Y, HANDLE hScreen); //Procediment per a esborrar objectes

void EsborrarQIX(int qixX, int qixY, HANDLE hScreen);  //Procediment per a esborrar el QIX
void EsborrarCursor(int CursorX, int CursorY, HANDLE hScreen);  //Procediment per a esborrar el cursor

int LlegirEvent();   //Funcio per a obtindre la tecla premuda

int Aleatori(int min, int max);   //Funcio per a crear un valor aleatori entre un mínim i un màxim (no pot ser 0)

void InicialitzacióDirQix(int &DirQixX, int &DirQixY); //Procediment per a inicialitzar la direcció del QIX (1 o -1)

void TractarEvent(int tecla, int &CursorX, int &CursorY, int qixX, int qixY, int &IniciX, int &IniciY, int &FiX, int &FiY, int &DirSTIX, int &Area, HANDLE hScreen);   //Procediment per a actuar depenent de la tecla premuda

void MoureQIX(int &qixX, int &qixY, int &DirQixX, int &DirQixY, int IniciX, int IniciY, int FiX, int FiY, int &color, HANDLE hScreen); //Procediment per a moure el QIX
void MoureCursor(int &CursorX, int &CursorY, int DirCursorX, int DirCursorY, HANDLE hScreen);  //Procediment per a moure el cursor

int MovimentSTIX_Dreta(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen);   //Funcions per a moure STIX
int MovimentSTIX_Esquerra(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen);
int MovimentSTIX_Adalt(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen);
int MovimentSTIX_Abaix(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen);

void PintarStix(int CursorX, int CursorY, HANDLE hScreen);  //Procediment per a pintar STIX

int QixXocStix(int qixX, int qixY, int cursorX, int cursorY, int DirStix); //Funcio per a determinar el xoc entre el QIX i el STIX

void PintarCuadroStix(int IniciX, int IniciY, int FiX, int FiY, HANDLE hScreen);  //Procesiment per a emplenar el quadrilater format pel STIX

void InfoPercentatgePartida(float percentatge, HANDLE hScreen);  //Procediment per a mostrar percentatge del objectiu

void ColorAleatori(int &color);  //Genera un valor aleatori que correspon a un color