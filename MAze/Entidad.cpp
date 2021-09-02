#include "Entidad.h"
Entidad::Entidad()
{
	this->x = this->y = this->dx = this->alto = this->ancho = this->dy = 0;
	IDx = 0;
}
int Entidad::GetX()
{
	return x;
}
int Entidad::GetY()
{
	return y;
}
int Entidad::GetDX()
{
	return dx;
}
int Entidad::GetDY()
{
	return dy;
}
int Entidad::GetAncho()
{
	return ancho;
}
int Entidad::GetAlto()
{
	return alto;
}

void Entidad::SetX(int value)
{
	x = value;
}
void Entidad::SetY(int value)
{
	y = value;
}
void Entidad::SetDX(int value)
{
	dx = value;
}
void Entidad::SetDY(int value)
{
	dy = value;
}
void Entidad::SetAncho(int value)
{
	ancho = value;
}
void Entidad::SetAlto(int value)
{
	alto = value;
}
int Entidad::GetIdx() {
	return IDx;
}

Rectangle Entidad::Area()
{
	return Rectangle(x, y, ancho, alto);
}

Rectangle Entidad::NextArea()
{
	return Rectangle(x + dx, y + dy, ancho, alto);
}
Rectangle Entidad::HitBox() {
	double alfa = 0.5;
	int altoA = alto * alfa;
	int anchoA = ancho * alfa;
	return Rectangle(x + anchoA / 2, y + altoA / 2, altoA, anchoA);
}
void Entidad::Mover(Graphics^ g)
{
	x += dx;
	y += dy;
}
void Entidad::Dibujar(Graphics^ g, Bitmap^ img)
{
	g->FillRectangle(Brushes::Black, x, y, ancho, alto);
}