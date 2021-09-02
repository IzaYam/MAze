#pragma once
#include "Entidad.h"
class Puerta :public Entidad
{
public:
	Puerta(int px, int py, Bitmap^ img);
	void Dibujar(Graphics^ g,Bitmap^img);
	~Puerta();
};
	