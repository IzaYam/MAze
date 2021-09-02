#include "Celda.h"
Celda::Celda(){

}
Celda::Celda(int ax, int ay) {

	this->i = ax;
	this->j = ay;
	this->w = 70; // tamaño de los cuadrados individuales para el laberinto
}
Rectangle Celda::Area() {
	return Rectangle(i * w, j * w, w, w);
}
void Celda::cambiar_pared(bool nuevo, int pos) {
	paredes[pos] = nuevo;
}

bool Celda::retornar_visitado() {
	return visitado;
}
void Celda::Cambiar_visitado(bool nuevo) {
	visitado = nuevo;
}
int Celda::retornar_i() {
	return i;
}
int Celda::retornar_j() {
	return j;
}
bool Celda::retornar_pared(int pos) {
	return paredes[pos];
}
void Celda::Dibujar(Graphics^ g) {
	int x = this->i * w;
	int y = this->j * w;
	if (paredes[0]) { //pared de arriba de cada cuadrado
		g->DrawLine(Pens::Black, x, y, x + w, y);
	}
	if (paredes[1]) { //pared derecha de cada cuadrado
		g->DrawLine(Pens::Black, x + w, y, x + w, y + w);
	}
	if (paredes[2]) { //pared de abajo de cada cuadrado
		g->DrawLine(Pens::Black, x + w, y + w, x, y + w);
	}
	if (paredes[3]) //pared izquierda de cada cuadrado
	{
		g->DrawLine(Pens::Black, x, y + w, x, y + w);
	}

}