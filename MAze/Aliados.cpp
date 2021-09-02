#include "Aliados.h"

Aliados::Aliados() {}
Aliados::Aliados(int px, int py, Bitmap^ aliados)
{
	x = px;
	y = py;
	this->ancho = aliados->Width / 13;
	this->alto = aliados->Height / 21;
	
	dx = 4;
	dy = 4;
	direccion = Caminar2Derecha;
}
void Aliados::Mover(Graphics^ g)
{
	switch(direccion)
	{
	case Caminar2Abajo: fila = 2;
		break;
	case Caminar2Izquierda: fila = 3;
		break;
	case Caminar2Derecha: fila = 1;
		break;
	case Caminar2Arriba: fila = 0;
		break;
	}
	x += dx;
	y += dy;
}
void Aliados::MoveType1(Graphics^ g)
{
	if (x + dx < g->VisibleClipBounds.Left) {
		direccion = Caminar2Derecha;
		dx *= -1;
	}
	if (x + dx + ancho > g->VisibleClipBounds.Right)
	{
		direccion = Caminar2Izquierda;
		dx = dx * -1;
	}
	if (y + dy < g->VisibleClipBounds.Top) {
		dy *= -1;

	}
	if (y + dy + alto > g->VisibleClipBounds.Bottom) {
		dy *= -1;

	}
	x += dx;
	y += dy;
}
void Aliados::Dibujar(Graphics^ g, Bitmap^ aliados)
{
	Rectangle corte = Rectangle(IDx * ancho, direccion * alto, ancho, alto);
	Rectangle zoom = Rectangle(x, y, ancho, alto);
	g->DrawImage(aliados, zoom, corte, GraphicsUnit::Pixel);
	if ((direccion >= Caminar2Arriba && direccion <= Caminar2Derecha) && dx != 0 || dy != 0)
		IDx = (IDx + 1) % 8;
	else if (direccion == Morir_enemigo)
		IDx = (IDx + 1) % 6;
}

int Aliados::Obtener_Ancho() { return ancho; }
int Aliados::Obtener_Alto() { return alto; }
void Aliados::Cambiar_direccion(SpriteEnemigo n) { direccion = n; }
Aliados::~Aliados() {}
