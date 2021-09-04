#include "Arreglo_Corrupts.h"
Arreglo_Corrupts::Arreglo_Corrupts() {

}
Arreglo_Corrupts::Arreglo_Corrupts(int n, Bitmap^ img_enemigo) {
	this->cant = 0;
	inicio = fin = nullptr;//lista vacia
	for (int i = 0; i < n; i++)
		AgregarCorrupt(img_enemigo);
}
void Arreglo_Corrupts::Eliminar_corrupt(int pos) {
	if (cant == 0)return;
	else if (cant == 1)
		inicio = fin = nullptr;
	else if (pos < cant - 1) {
		//eliminar si esta al inicio
		if (pos == 0) {
			if (cant == 0)return;
			else if (cant == 1)
				fin = nullptr;
			NodoD<Corrupt>* aux = inicio;
			inicio = inicio->siguiente;
			inicio->anterior = nullptr;
			delete aux;
			--cant;
		}
		//eliminar si no esta en el final
		else {
			NodoD<Corrupt>* aux = inicio;

			for (int i = 0; i < pos - 1; ++i)
				aux = aux->siguiente;

			NodoD<Corrupt>* eliminar = aux->siguiente;
			aux->siguiente = eliminar->siguiente;
			eliminar->siguiente->anterior = aux;

			delete eliminar;

			--cant;
		}
	}
	//eliminar si esta en el final
	else if (pos + 1 == cant) {
		if (cant == 0)return;
		else if (cant == 1) {
			delete fin;
			inicio = fin = nullptr;
			--cant;
		}
		else {
			fin = fin->anterior;
			delete fin->siguiente;
			fin->siguiente = nullptr;
			--cant;
		}
	}

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