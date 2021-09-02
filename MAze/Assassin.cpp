#include "Assassin.h"
Assassin::Assassin() {

}
Assassin::Assassin(int px, int py, Bitmap^ img) {
	this->x = px;
	this->y = py;
	this->dx = rand()%(6-4+1)+4;
	this->dy = rand()%(6-4+1)+4;
	this->ancho = img->Width / 13;
	this->alto = img->Height / 21;
	colisionado = false;
	dir = SpriteEnemigo::Caminar2Derecha;
}
SpriteEnemigo Assassin::retornar_direccion() {
	return dir;
}
void Assassin::Mover(Graphics^ g) {
	if (x + dx < g->VisibleClipBounds.Left) {
		dir = Caminar2Derecha;
		dx *= -1;
	}
	if (x + dx + ancho > g->VisibleClipBounds.Right)
	{
		dir = Caminar2Izquierda;
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
void Assassin::Dibujar(Bitmap^ img, Graphics^ g) {
	Rectangle corte = Rectangle(IDx * ancho, dir * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
	

	g->DrawRectangle(Pens::Orange, HitBox());
	if ((dir >= Caminar2Arriba && dir <= Caminar2Derecha) && dx != 0 || dy != 0)
		IDx = (IDx + 1) % 8;
	else if (dir == Morir_enemigo)
		IDx = (IDx + 1) % 6;
}

void Assassin::Cambiar_direccion(SpriteEnemigo nuevo)
{
	dir = nuevo;
}
bool Assassin::retornar_colisionado() {
	return colisionado;
}
void Assassin::cambiar_colisionado(bool nuevo) {
	colisionado = nuevo;
}