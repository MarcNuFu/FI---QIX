#include "Joc.h"

int Joc(int dificultat)
{
	HANDLE hScreen;         //Declaració de variable per a modificar el tamany de la pantalla i la seva utilització
	hScreen = GetStdHandle(STD_OUTPUT_HANDLE);
	InitScreen(hScreen);

	srand((unsigned)time(NULL));   //Utilitzem srand per fer efectiva la aleatorietat

	int XocStix;   //Variable per al xoc de l'Stix, 1=Xoc  0=No Xoc

	int nivell = 1;

	unsigned char tecla = 0;  //Variable per a les tecles premudes

	int qixX, qixY;  //Variables de posició del QIX/
	int CursorX, CursorY;  //Variables de posició del cursor

	int IniciX, FiX;  //Límits variables de X
	int IniciY, FiY;  //Límits variables de Y

	int DirStix;  //Variable de direcció del Stix
	int DirQixX, DirQixY;  //Variables de direccio del QIX

	bool viu;  //Variable de vida, true=viu  false=mort
	int vides = 3;  //Variable de la quantitat de vides

	int punts = 0, puntsact = 0;  //Varables per a controlar els punts, punts -> punt definitius, puntsact -> punts actuals - es perden al morir. D'aquesta forma no s'acumulen punts encara que perdis (com al QIX original)
	int Area, AreaTotal;  //Varaibles per a controlar la area formada
	bool nivellcompletat;  //Variable per a controlar si s'ha completat un nivell o no, false=Nivell no superat   true=Nivell superat

	float percentatge = 0;  //Variable per a mostrar el percentatge actual de l'objectiu

	int VelocitatQix = (0.5+(1/dificultat))*(VELOCITATPC - (nivell*(VELOCITATPC / 5)));  //Variable que controla la velocitat del QIX
	int NCops = 0;

	int color = LIGHTGREY;  //Varaible per a modificar el color del QIX

	do
	{
		qixX = (FI_X - INICI_X) / 2 + INICI_X; qixY = (FI_Y - INICI_Y) / 2 + INICI_Y;  //Inicialització de la posició QIX
		CursorX = (FI_X - INICI_X) / 2 + INICI_X; CursorY = FI_Y;  //Inicialització de la posició del cursor
		InicialitzacióDirQix(DirQixX, DirQixY);  //Inicialitzar direcció del QIX aleatoriament

		IniciX = INICI_X; FiX = FI_X;  //Límits variables de X
		IniciY = INICI_Y; FiY = FI_Y;  //Límits variables de Y

		DirStix = MOV_PARAT;  //Direcció Stix comença parada

		viu = true;
		nivellcompletat = false;
		AreaTotal = 0;
		Area = 0;
		puntsact = 0;

		XocStix = 0;

		percentatge = 0;

		system("cls");
		Taulell(hScreen);                //Dibuixar taulell

		InfoPuntsPartida(punts, hScreen);  //Escriure Punts
		InfoNivellPartida(nivell, hScreen);  //Escriure Nivell
		InfoVidesPartida(vides, hScreen);  //Escriure Vides

		InfoPercentatgePartida(percentatge, hScreen);  //Mostra el percentatge actual

		PintarQIX(qixX, qixY, color, hScreen);  //Pintar QIX
		PintarCursor(CursorX, CursorY, hScreen);  //Pintar Cursor

		do //El joc s'executarà fins a premer ESC, superar el nivell o morir
		{
			if (_kbhit())
			{
				tecla = LlegirEvent();  //Llegir tecla premuda
				TractarEvent(tecla, CursorX, CursorY, qixX, qixY, IniciX, IniciY, FiX, FiY, DirStix, Area, hScreen);  //Actuar segons tecla premuda

				if (Area)
				{
					puntsact += Area;
					InfoPuntsPartida(puntsact+punts, hScreen);
					AreaTotal += Area;

					percentatge = float(AreaTotal * 100) / float(AREARECTANGLE);
					InfoPercentatgePartida(percentatge, hScreen);

					Area = 0;
					if (AreaTotal >= ((3 * AREARECTANGLE)/ 4))
					{
						nivellcompletat = true;
					}
				}
			}

			NCops++;

			if (NCops >= VelocitatQix)
			{
				MoureQIX(qixX, qixY, DirQixX, DirQixY, IniciX, IniciY, FiX, FiY, color, hScreen);  //Moure el QIX

				if (DirStix != MOV_PARAT)
				{
					XocStix = QixXocStix(qixX, qixY, CursorX, CursorY, DirStix);
					if (XocStix == 1)
					{
						viu = false;
					}
				}
				NCops = 0;
			}
	
		} while ((viu == true) && (tecla != TECLA_ESC) && (nivellcompletat == false));

		if (viu == false)  //Si el jugador mor
		{
			vides--;  //Restem vides
		}

		if (nivellcompletat == true)  //Si el jugador es passa el nivell
		{
			punts += puntsact;  //Sumem els punts de la ronda als punts definitius
			nivell++;  //Avaçem un nivell
			nivellcompletat = false;
			AreaTotal = 0;
		}

		Sleep(2000);

	} while ((tecla != TECLA_ESC) && (vides > 0) && (nivell < 4));

	if (vides <= 0)
	{
		GameOver(hScreen);      //Escriure GAME OVER
	    
		_getch(); _getch();
	}

	return punts;
}



void Taulell(HANDLE hScreen)  
{
	TextColor(LIGHTGREY, BLACK, hScreen); 

	for (int x = INICI_X; x <= FI_X; x++)    //Bucle per a pintar linea taulell superior i  inferior
	{
		GotoXY(x, INICI_Y, hScreen);
		cout << char(MUR);
		GotoXY(x, FI_Y, hScreen);
		cout << char(MUR);
	}

	for (int y = INICI_Y; y <= FI_Y; y++)    //Bucle per a pintar linea taulell esquerra i dreta
	{
		GotoXY(INICI_X, y, hScreen);
		cout << char(MUR);
		GotoXY(FI_X, y, hScreen);
		cout << char(MUR);
	}
}

void InfoPuntsPartida(int punts, HANDLE hScreen)
{
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(INICI_X + 2, INICI_Y - 4, hScreen);
	cout << "Punts: " << punts;
}

void InfoVidesPartida(int vides, HANDLE hScreen)
{
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(INICI_X + 2, INICI_Y - 2, hScreen);
	cout << "Vides: " << vides;
}

void InfoNivellPartida(int nivell, HANDLE hScreen)
{
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(FI_X - 8, INICI_Y - 4, hScreen);
	cout << "Nivell: " << nivell;
}

void PintarQIX(int qixX, int qixY, int color, HANDLE hScreen)  
{
	TextColor(color, BLACK, hScreen);    
	GotoXY(qixX, qixY, hScreen);
	cout << char(MUR);
}

void PintarCursor(int cursorX, int cursorY, HANDLE hScreen)  
{
	TextColor(RED, BLACK, hScreen);   
	GotoXY(cursorX, cursorY, hScreen);
	cout << char(MUR);
}

void EsborrarQIX(int x, int y, HANDLE hScreen) 
{
	TextColor(BLACK, BLACK, hScreen);
	GotoXY(x, y, hScreen);
	cout << char(MUR);
}

void EsborrarCursor(int x, int y, HANDLE hScreen) 
{
	TextColor(LIGHTGREY, BLACK, hScreen);  
	GotoXY(x, y, hScreen);
	cout << char(MUR);
}

void GameOver(HANDLE hScreen)  
{
	TextColor(LIGHTGREY, BLACK, hScreen);      
	GotoXY((FI_X - INICI_X) / 2, (FI_Y - INICI_Y) / 2 + INICI_Y, hScreen);
	cout << "GAME OVER";
}

void PintarObjecte(int X, int Y, char Obj, int ColorObj, HANDLE hScreen)  
{
	TextColor(ColorObj, BLACK, hScreen);
	GotoXY(X, Y, hScreen);
	cout.put(Obj);
}

void EsborrarObjecte(int X, int Y, HANDLE hScreen)  
{
	TextColor(BLACK, BLACK, hScreen);
	GotoXY(X, Y, hScreen);
	cout << char(MUR);
}

int LlegirEvent()  
{
	int tecla = 0;

	tecla = _getch(); //Lectura tecla

	if (tecla == TECLA_ESTESA) // S'ha premut una tecla estesa
	{ 
		tecla = _getch(); // Llegir segona part tecla
	}
	return tecla;

}

int Aleatori(int min, int max)  
{
	int num;
	do
	{
		num = rand() % (max - min + 1) + min;
	} while (num == 0);  //Repetir fins a trobar un valor diferent de 0
	return (num);
}

void InicialitzacióDirQix(int &DirQixX, int &DirQixY)  
{
	DirQixX = Aleatori(-1, 1);
	DirQixY = Aleatori(-1, 1);
}

void TractarEvent(int tecla, int &CursorX, int &CursorY, int qixX, int qixY, int &IniciX, int &IniciY, int &FiX, int &FiY, int &DirSTIX, int &Area, HANDLE hScreen)
{
	int Stix;

	switch (tecla)
	{
	case 'd':
	case 'D':
	case TECLA_DRETA:  //Tecla dreta premuda
		if ((CursorX < FiX) && ((CursorY == IniciY) || (CursorY == FiY)))
		{
			MoureCursor(CursorX, CursorY, 1, 0, hScreen);  //Moure cursor cap a la dreta
		}

		Stix = MovimentSTIX_Dreta(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorY > qixY)
			{
				PintarCuadroStix(IniciX + 1, CursorY + 1, FiX - 1, FiY - 1, hScreen);
				Area = (FiX - IniciX)*(FiY - CursorY);
				FiY = CursorY;
			}
			else
			{
				PintarCuadroStix(IniciX + 1, IniciY + 1, FiX - 1, CursorY - 1, hScreen);
				Area = (FiX - IniciX)*(CursorY - IniciY);
				IniciY = CursorY;
			}
		}
		break;
	case 'a':
	case 'A':
	case TECLA_ESQUERRA:  //Tecla esquerra premuda
		if ((CursorX > IniciX) && ((CursorY == IniciY) || (CursorY == FiY)))
		{
			MoureCursor(CursorX, CursorY, -1, 0, hScreen);  //Moure cursor cap a l'esquerra
		}

		Stix = MovimentSTIX_Esquerra(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorY > qixY)
			{
				PintarCuadroStix(IniciX + 1, CursorY + 1, FiX - 1, FiY - 1, hScreen);
				Area = (FiX - IniciX)*(FiY - CursorY);
				FiY = CursorY;
			}
			else
			{
				PintarCuadroStix(IniciX + 1, IniciY + 1, FiX - 1, CursorY - 1, hScreen);
				Area = (FiX - IniciX)*(CursorY - IniciY);
				IniciY = CursorY;
			}
		}
		break;
	case 'w':
	case 'W':
	case TECLA_ADALT:  //Tecla superior premuda
		if ((CursorY > IniciY) && ((CursorX == IniciX) || (CursorX == FiX)))
		{
			MoureCursor(CursorX, CursorY, 0, -1, hScreen);  //Moure cursor cap adalt
		}

		Stix = MovimentSTIX_Adalt(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorX > qixX)
			{
				PintarCuadroStix(CursorX + 1, IniciY + 1, FiX - 1, FiY - 1, hScreen);
				Area = (FiY - IniciY)*(FiX - CursorX);
				FiX = CursorX;
			}
			else
			{
				PintarCuadroStix(IniciX + 1, IniciY + 1, CursorX - 1, FiY - 1, hScreen);
				Area = (FiY - IniciY)*(CursorX - IniciX);
				IniciX = CursorX;
			}
		}
		break;
	case 's':
	case 'S':
	case TECLA_ABAIX:  //Tecla inferior premuda
		if ((CursorY < FiY) && ((CursorX == IniciX) || (CursorX == FiX)))
		{
			MoureCursor(CursorX, CursorY, 0, 1, hScreen);  //Moure cursor cap abaix
		}

		Stix = MovimentSTIX_Abaix(CursorX, CursorY, IniciX, IniciY, FiX, FiY, DirSTIX, hScreen);
		if (Stix)
		{
			if (CursorX > qixX)
			{
				PintarCuadroStix(CursorX + 1, IniciY + 1, FiX - 1, FiY - 1, hScreen);
				Area = (FiY - IniciY)*(FiX - CursorX);
				FiX = CursorX;
			}
			else
			{
				PintarCuadroStix(IniciX + 1, IniciY + 1, CursorX - 1, FiY - 1, hScreen);
				Area = (FiY - IniciY)*(CursorX - IniciX);
				IniciX = CursorX;
			}
		}
		break;
	}

}

void MoureQIX(int &qixX, int &qixY, int &DirQixX, int &DirQixY, int IniciX, int IniciY, int FiX, int FiY, int &color, HANDLE hScreen)   
{
	static int RecorregutQix = 0;  //Variable estàtica per al moviment erràtic

	EsborrarQIX(qixX, qixY, hScreen);  //Esborrar QIX

	if (RecorregutQix == 0)   //Inicialitzar una altra vegada la direcció del QIX (Moviment erràtic) quan el recorregut arriba al seu límit
	{
		RecorregutQix = Aleatori(5, 20);  //Nou límit per al recorregut
		InicialitzacióDirQix(DirQixX, DirQixY);
		ColorAleatori(color);
	}

	if (qixX + DirQixX <= IniciX || qixX + DirQixX >= FiX)   //Si el QIX arriba al laterals canvia de sentit
	{
		DirQixX *= -1;
		ColorAleatori(color);
	}
	if (qixY + DirQixY <= IniciY || qixY + DirQixY >= FiY)    //Si el QIX arriba al limits verticals canvia de sentit
	{
		DirQixY *= -1;
		ColorAleatori(color);
	}

	qixY += DirQixY;     //Modifiquem valor Y del QIX
	qixX += DirQixX;     //Modifiquem valor X del QIX

	PintarQIX(qixX, qixY, color, hScreen);  //Pintar QIX

	RecorregutQix--;
}

void MoureCursor(int &CursorX, int &CursorY, int DirCursorX, int DirCursorY, HANDLE hScreen)  
{
	EsborrarCursor(CursorX, CursorY, hScreen);  //Esborrar cursor (Pintar de blanc)

	if (DirCursorX == 1)  //Cursor cap a la dreta
	{
		CursorX++;
	}
	if (DirCursorX == -1)  //Cursor cap a l'esquerra
	{
		CursorX--;
	}
	if (DirCursorY == 1)  //Cursor cap a baix
	{
		CursorY++;
	}
	if (DirCursorY == -1)  //Cursor cap a dalt
	{
		CursorY--;
	}

	PintarCursor(CursorX, CursorY, hScreen);  //Pintar cursor
}

int MovimentSTIX_Dreta(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{
	int StixAconseguit = 0;
	int DirCursorX, DirCursorY;

	if ((CursorX == IniciX) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = 1; DirCursorY = 0;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_DRETA;
	}
	else
	{
		if ((CursorX < FiX) && (DirSTIX == MOV_DRETA))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorX++;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorX == FiX)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

int MovimentSTIX_Esquerra(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{
	int StixAconseguit = 0;
	int DirCursorX, DirCursorY;

	if ((CursorX == FiX) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = -1; DirCursorY = 0;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_ESQUERRA;
	}
	else
	{
		if ((CursorX > IniciX) && (DirSTIX == MOV_ESQUERRA))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorX--;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorX == IniciX)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

int MovimentSTIX_Adalt(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{
	int DirCursorX, DirCursorY;
	int StixAconseguit = 0;

	if ((CursorY == FiY) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = 0; DirCursorY = -1;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_ADALT;
	}
	else
	{
		if ((CursorY > IniciY) && (DirSTIX == MOV_ADALT))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorY--;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorY == IniciY)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

int MovimentSTIX_Abaix(int &CursorX, int &CursorY, int IniciX, int IniciY, int FiX, int FiY, int &DirSTIX, HANDLE hScreen)
{
	int DirCursorX, DirCursorY;
	int StixAconseguit = 0;

	if ((CursorY == IniciY) && (DirSTIX == MOV_PARAT))
	{
		DirCursorX = 0; DirCursorY = 1;
		MoureCursor(CursorX, CursorY, DirCursorX, DirCursorY, hScreen);
		DirSTIX = MOV_ABAIX;
	}
	else
	{
		if ((CursorY < FiY) && (DirSTIX == MOV_ABAIX))
		{
			PintarStix(CursorX, CursorY, hScreen);
			CursorY++;
			PintarCursor(CursorX, CursorY, hScreen);
			if (CursorY == FiY)
			{
				DirSTIX = MOV_PARAT;
				StixAconseguit = 1;
			}
		}
	}
	return StixAconseguit;
}

void PintarStix(int CursorX, int CursorY, HANDLE hScreen)
{
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(CursorX, CursorY, hScreen);
	cout << char(MUR);
}

int QixXocStix(int qixX, int qixY, int cursorX, int cursorY, int DirStix)
{
	int xoc = 0;

	switch (DirStix)
	{
	case MOV_DRETA:
		if ((cursorY == qixY) && (cursorX >= qixX))
		{
			xoc = 1;
		}
		break;
	case MOV_ESQUERRA:
		if ((cursorY == qixY) && (cursorX <= qixX))
		{
			xoc = 1;
		}
		break;
	case MOV_ADALT:
		if ((cursorX == qixX) && (cursorY <= qixY))
		{
			xoc = 1;
		}
		break;
	case MOV_ABAIX:
		if ((cursorX == qixX) && (cursorY >= qixY))
		{
			xoc = 1;
		}
		break;
	}

	return (xoc);
}

void PintarCuadroStix(int IniciXCuadro, int IniciYCuadro, int FiXCuadro, int FiYCuadro, HANDLE hScreen)
{
	TextColor(CYAN, BLACK, hScreen);

	int y = IniciYCuadro;

	while (y <= FiYCuadro)
	{
		for (int x = IniciXCuadro; x <= FiXCuadro; x++)    
		{
			GotoXY(x, y, hScreen);
			cout << char(MUR);
		}
		y++;
	}
}

void InfoPercentatgePartida(float percentatge, HANDLE hScreen)
{
	TextColor(LIGHTGREY, BLACK, hScreen);
	GotoXY(FI_X - 8, INICI_Y - 2, hScreen);
	cout << "75% - "; 
	cout.precision(4); //Fixar xifres a 4
	cout << percentatge;
	cout << "%      ";
}

void ColorAleatori(int &color)
{
	int aux;

	do  //Bulce fins a trovar un color diferent a l'actual
	{
		aux = rand() % 6 + 9;;
	} while (aux == color);

	color = aux;
}