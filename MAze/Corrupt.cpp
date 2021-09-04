#include "Corrupt.h"
Corrupt::Corrupt() {

}
Corrupt::Corrupt(int px, int py, Bitmap^ img){
	this->x = px;
	this->y = py;
	this->dx = 3;
	this->dy = 3;
	this->ancho = img->Width / 13; 
	this->alto = img->Height / 21;
	colisionado = false;
	dir = SpriteEnemigo::Caminar2Derecha;
}
SpriteEnemigo Corrupt::retornar_direccion() {
	return dir;
}
void Corrupt::Mover(Graphics^ g) {
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
void Corrupt::Dibujar(Bitmap^ img, Graphics^ g,Bitmap^cambio) {
	Rectangle corte = Rectangle(IDx * ancho, dir * alto, ancho, alto);
	if (colisionado == false) {
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
	}
	else {
		g->DrawImage(cambio, Area(), corte, GraphicsUnit::Pixel);
	}
	//g->DrawRectangle(Pens::Orange, HitBox());
	if ((dir >= Caminar2Arriba && dir <= Caminar2Derecha) && dx != 0 || dy != 0)
		IDx = (IDx + 1) % 8;
	else if (dir == Morir_enemigo)
		IDx = (IDx + 1) % 6;
}

void Corrupt::Cambiar_direccion(SpriteEnemigo nuevo)
{
	dir = nuevo;
}
bool Corrupt::retornar_colisionado() {
	return colisionado;
}
void Corrupt::cambiar_colisionado(bool nuevo) {
	colisionado = nuevo;
}
void Corrupt::Mover_Oculto(Graphics^ g) {
	if (x + dx + ancho <= g->VisibleClipBounds.Width / 2) {
		x += dx;
		dir = Caminar2Derecha;
	}
}