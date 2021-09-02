#include "Puerta.h"

Puerta::Puerta(int px, int py, Bitmap^ img) {
	this->alto = img->Height / 15;
	this->ancho = img->Width / 15;
	this->x = px;
	this->y = py;
	this->dx = this->dy = 0;
}
void Puerta::Dibujar(Graphics^ g,Bitmap^img) {
	g->DrawImage(img,Area());
}