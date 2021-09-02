#pragma once
#include "Entidad.h"
class Assassin :
    public Entidad
{
private:
	SpriteEnemigo dir;
	bool colisionado;

public:
	Assassin();
	Assassin(int px, int py, Bitmap^ img);
	SpriteEnemigo retornar_direccion();
	void Mover(Graphics^ g);

	void Dibujar(Bitmap^ img, Graphics^ g);
	void Cambiar_direccion(SpriteEnemigo nuevo);
	bool retornar_colisionado();
	void cambiar_colisionado(bool nuevo);
};


