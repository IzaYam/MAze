#pragma once
#include "Celda.h"
#include <time.h>
#include <vector>
#include "Personaje.h"
#include <iostream>

using namespace std;



class Laberinto
{
public:
	int cols, rows;
	vector<Celda*>grid;
	Celda* current;
	vector<Celda*>stack;

public:
	Laberinto() ;
	void Iniciar(Graphics^ g) ;	
	void Dibujar(Graphics^ g) ;	
	Celda* Rectornar_celda(int i) ;
	Celda* Verificar_Vecino(Celda* celda) ;
	int index(int i, int  j) ;
	void Remover_Pared(Celda* a, Celda* b);
	int retornar_cant();
	void Dibujar_Current(Graphics^g) ;
	Celda* colision(Rectangle per);
};
