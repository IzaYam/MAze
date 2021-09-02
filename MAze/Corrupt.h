#pragma once
#include "Entidad.h"
#include "ArrAliados.h"
/*CORRUPTS*/
class Corrupt :public Entidad
{
private:
	SpriteEnemigo dir;
	bool colisionado;

public:
	Corrupt();
	Corrupt(int px, int py, Bitmap^ img);
	SpriteEnemigo retornar_direccion();
	void Mover(Graphics^ g);
	
	void Dibujar(Bitmap^ img, Graphics^ g,Bitmap^cambio);
	void Cambiar_direccion(SpriteEnemigo nuevo);
	bool retornar_colisionado();
	void cambiar_colisionado(bool nuevo);
	void Mover_Oculto(Graphics^ g);
};

