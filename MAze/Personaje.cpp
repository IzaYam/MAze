#include "Personaje.h"
Jugador::Jugador(Bitmap^ img)
{
	x = 1;
	y = 1;
	dx = dy = 0;
	ancho = img->Width / 11;
	alto = img->Height / 13;

	accion = CaminarAbajo;
}
void Jugador::SetAccion(SpriteJugador value)
{
	if (accion != value)
		IDx = 0;
	accion = value;
}
SpriteJugador Jugador::GetAccion() {
	return accion;
}
void Jugador::Mover(Graphics^ g)
{
	if (x + dx >= 0 && x + dx + ancho < g->VisibleClipBounds.Width)
		x += dx;
	if (y + dy >= 0 && y + dy + alto < g->VisibleClipBounds.Height)
		y += dy;
}
void Jugador::Dibujar(Graphics^ g, Bitmap^ img)
{
	Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
	g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
	g->DrawRectangle(Pens::Red, HitBox());


	if (accion >= AtacarArriba && accion <= AtacarDerecha) {
		IDx = (IDx + 1) % 8;
		if (IDx == 0) {
			if (accion == AtacarArriba)
				accion = CaminarArriba;
			if (accion == AtacarAbajo)
				accion = CaminarAbajo;
			if (accion == AtacarIzquierda)
				accion = CaminarIzquierda;
			if (accion == AtacarDerecha)
				accion = CaminarDerecha;
		}
	}
	else if ((accion >= CaminarArriba && accion <= CaminarDerecha) && dx != 0 || dy != 0)
		IDx = (IDx + 1) % 9;
	else if (accion >= DispararArriba && accion <= DispararDerecha)
		IDx = (IDx + 1) % 11;
	else if (accion == Morir)
		IDx = (IDx + 1) % 6;

}