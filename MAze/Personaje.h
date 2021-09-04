#pragma once
#include "Entidad.h"



class Jugador : public Entidad
{
	SpriteJugador accion;

public:
	Jugador(Bitmap^ img, int x, int y);
	void SetAccion(SpriteJugador value);
	SpriteJugador GetAccion();
	void Mover(Graphics^ g);
	void Dibujar(Graphics^ g, Bitmap^ img);
};
