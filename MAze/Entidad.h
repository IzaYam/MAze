#pragma once
#include <iostream>
#include <time.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
public enum SpriteJugador
{
	AtacarArriba,
	AtacarIzquierda,
	AtacarAbajo,
	AtacarDerecha,

	CaminarArriba,
	CaminarIzquierda,
	CaminarAbajo,
	CaminarDerecha,

	DispararArriba,
	DispararIzquieda,
	DispararAbajo,
	DispararDerecha,

	Morir
};
public enum SpriteEnemigo
{
	Bailar2Arriba,
	Bailar2Izquierda,
	Bailar2Abajo,
	Bailar2Derecha,

	Atacar2Arriba,
	Atacar2Izquierda,
	Atacar2Abajo,
	Atacar2Derecha,

	Caminar2Arriba,
	Caminar2Izquierda,
	Caminar2Abajo,
	Caminar2Derecha,

	Apuntar2Arriba,
	Apuntar2Izquierda,
	Apuntar2Abajo,
	Apuntar2Derecha,

	Disparar2Arriba,
	Disparar2Izquieda,
	Disparar2Abajo,
	Disparar2Derecha,

	Morir_enemigo
};


class Entidad
{
protected:
	int x, y;
	int dx, dy;
	int ancho, alto;

	int IDx;
public:
	Entidad();
	int GetX();
	int GetY();
	int GetDX();
	int GetDY();
	int GetAncho();
	int GetAlto();

	void SetX(int value);
	void SetY(int value);
	void SetDX(int value);
	void SetDY(int value);
	void SetAncho(int value);
	void SetAlto(int value);
	int GetIdx();
	Rectangle Area();
	
	Rectangle NextArea();
	Rectangle HitBox();
	virtual void Mover(Graphics^ g);
	virtual void Dibujar(Graphics^ g, Bitmap^ img);
};