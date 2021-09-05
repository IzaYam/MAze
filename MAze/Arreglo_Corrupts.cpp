#include "Arreglo_Corrupts.h"
Arreglo_Corrupts::Arreglo_Corrupts() {

}
Arreglo_Corrupts::Arreglo_Corrupts(int n, Bitmap^ img_enemigo) {
	this->cant = 0;
	inicio = fin = nullptr;//lista vacia
	for (int i = 0; i < n; i++)
		AgregarCorrupt(img_enemigo);
}

int Arreglo_Corrupts::retornar_cant() {
	return cant;
}

NodoD<Corrupt>* Arreglo_Corrupts::Retornar_corrupt(int pos) {
	return RecursivoRetornar(inicio, pos, 0);

}
NodoD<Corrupt>* Arreglo_Corrupts::RecursivoRetornar(NodoD<Corrupt>* i, int pos, int s) {
	NodoD<Corrupt>* aux = i;
	if (pos < cant) {
		if (s < pos) {
			aux = aux->siguiente;
			return RecursivoRetornar(aux, pos, ++s);
		}
		else return aux;
	}

}
void Arreglo_Corrupts::Mover_Corrupts(Graphics^ g) {
	for (int i = 0; i < cant; i++)
	{
		Retornar_corrupt(i)->elemento.Mover(g);
	}
}
void Arreglo_Corrupts::Graficar_Corrupts(Bitmap^ img_enemigo, Graphics^ g, Bitmap^ img_aliado) {
	for (int i = 0; i < cant; i++)
	{
		Retornar_corrupt(i)->elemento.Dibujar(img_enemigo, g, img_aliado);
	}
}
void Arreglo_Corrupts::Colision_Aliado_Corrupt(ArrAliados* arreglo_aliados, Bitmap^ img) {
	for (int i = 0; i < arreglo_aliados->retornar_cant(); i++)
	{
		Rectangle Aliado = Rectangle(arreglo_aliados->retornar_pos_aliado(i)->HitBox());
		for (int j = 0; j < cant; j++)
		{
			Rectangle Enemigo = Rectangle(Retornar_corrupt(j)->elemento.HitBox());
			if (Enemigo.IntersectsWith(Aliado)) {
				arreglo_aliados->Eliminar_aliado(i);
				AgregarCorrupt(img);


			}

		}
	}
}
void Arreglo_Corrupts::AgregarCorrupt(Bitmap^ img_enemigo) {
	NodoD<Corrupt>* nuevo = new NodoD<Corrupt>(Corrupt(rand() % (1000 - 800 + 1) + 800, rand() % (400 + 1), img_enemigo));
	if (cant == 0)
		inicio = nuevo;
	else {
		NodoD<Corrupt>* aux = inicio;
		while (aux->siguiente != nullptr) {
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}
	++cant;
}