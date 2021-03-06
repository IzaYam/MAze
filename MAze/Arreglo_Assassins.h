#pragma once
#include "Assassin.h"
/*ASSASINS*/

template<class T>
struct Nodo {
	T elemento;
	Nodo<T>* siguiente;
	Nodo(T v, Nodo<T>* sig = NULL) {
		siguiente = sig;
		elemento = v;
	}
};

class Arreglo_Assassins
{
private:
	Nodo<Assassin>* inicio;
	Nodo<Assassin>* fin;
	
	int cant;
public:

	Arreglo_Assassins();
	Arreglo_Assassins(int n, Bitmap^ img_enemigo);
	void AgregarAsesino(Bitmap^ img_enemigo);
	void Mover_asesinos(Graphics^ g);
	void Graficar_asesinos(Bitmap^ img_asesino, Graphics^ g);
	int retornar_cant();
	Nodo<Assassin>* Retornar_asesino(int pos);
	Nodo<Assassin>* RecursivoRetornar(Nodo<Assassin>* i,int pos, int s);
	bool Colision_Jugador_Asesino(Rectangle jug);


};

