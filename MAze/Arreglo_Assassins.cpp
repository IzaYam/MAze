#include "Arreglo_Assassins.h"
Arreglo_Assassins::Arreglo_Assassins() {

}
Arreglo_Assassins::Arreglo_Assassins(int n, Bitmap^ img_enemigo) {
	this->cant = 0;
	for (int i = 0; i < n; i++)
		AgregarAsesino(img_enemigo);
}

int Arreglo_Assassins::retornar_cant() {
	return cant;
}
Nodo<Assassin>* Arreglo_Assassins::Retornar_asesino(int pos) {
	return RecursivoRetornar(inicio,pos,0);

}
Nodo<Assassin>* Arreglo_Assassins::RecursivoRetornar(Nodo<Assassin>* i,int pos, int s) {
	Nodo<Assassin>* aux = i;
	if (pos < cant) {
		if (s < pos) {
			aux = aux->siguiente;
			return RecursivoRetornar(aux, pos, ++s);
		}
		else return aux;
	}
}


void Arreglo_Assassins::Mover_asesinos(Graphics^ g) {
	for (int i = 0; i < cant; i++)
	{
		Retornar_asesino(i)->elemento.Mover(g);
	}
}
void Arreglo_Assassins::Graficar_asesinos(Bitmap^ img_asesino, Graphics^ g) {
	for (int i = 0; i < cant; i++)
	{
		Retornar_asesino(i)->elemento.Dibujar(img_asesino, g);
	}
}
bool Arreglo_Assassins::Colision_Jugador_Asesino(Rectangle jug) {
	bool choco = false;
	Rectangle jugador = jug;
	Rectangle asesino;
	for (int i = 0; i < cant; i++)
	{
		asesino = Retornar_asesino(i)->elemento.HitBox();
		if (asesino.IntersectsWith(jugador)) {
			choco = true;
		}
	}
	return choco;
}
void Arreglo_Assassins::AgregarAsesino(Bitmap^ img_enemigo) {
	Nodo<Assassin>* nuevo = new Nodo<Assassin>(Assassin(rand() % (1000 - 800 + 1) + 800, rand() % (400 + 1), img_enemigo));
	if (cant == 0)
		inicio = nuevo;
	else {
		Nodo<Assassin>* aux = inicio;
		while (aux->siguiente != nullptr) {
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}
	++cant;
}