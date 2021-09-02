#pragma once
#include "Entidad.h"
class Aliados : public Entidad
{
private:
	SpriteEnemigo direccion;
	int fila, columna;

public:
	Aliados();
	Aliados(int px, int py, Bitmap^ aliados);
	void Mover(Graphics^ g);
	void MoveType1(Graphics^ g);
	void Dibujar(Graphics^ g, Bitmap^ aliados);

	int Obtener_Ancho();
	int Obtener_Alto();
	void Cambiar_direccion(SpriteEnemigo n);
	~Aliados();
};

