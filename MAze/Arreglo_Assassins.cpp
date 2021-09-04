#include "Arreglo_Assassins.h"
Arreglo_Assassins::Arreglo_Assassins() {

}
Arreglo_Assassins::Arreglo_Assassins(int n, Bitmap^ img_enemigo) {
	this->cant = 0;
	for (int i = 0; i < n; i++)
		AgregarAsesino(img_enemigo);
}
void Arreglo_Assassins::Eliminar_Asesino(int pos) {
	if (cant == 0)return;
	else if (cant == 1)
		inicio = fin = nullptr;
	else if (pos < cant - 1) {
		//eliminar si esta al inicio
		if (pos == 0) {
			if (cant == 0)return;
			else if (cant == 1)
				fin = nullptr;
			Nodo<Assassin>* aux = inicio;
			inicio = inicio->siguiente;
			delete aux;
			--cant;
		}
		//eliminar si no esta en el final
		else {
			Nodo<Assassin>* aux = inicio;

			for (int i = 0; i < pos - 1; ++i)
				aux = aux->siguiente;

			Nodo<Assassin>* eliminar = aux->siguiente;
			aux->siguiente = eliminar->siguiente;
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
			delete fin->siguiente;
			fin->siguiente = nullptr;
			--cant;
		}
	}

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
			Eliminar_Asesino(i);
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