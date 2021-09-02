#pragma once
#include "Corrupt.h"
using namespace std;
template <typename Tipo>
struct NodoD {
	Tipo elemento;
	NodoD<Tipo>* siguiente;
	NodoD<Tipo>* anterior;
	NodoD(Tipo v, NodoD<Tipo>* s = nullptr, NodoD<Tipo>* a = nullptr) {
		elemento = v;
		siguiente = s;
		anterior = a;
	}
};
class Arreglo_Corrupts
{
	NodoD<Corrupt>* inicio;
	NodoD<Corrupt>* fin;
	int cant;
public:
	class Iterador {
		NodoD<Corrupt>* aux;

	public:
		Iterador(NodoD<Corrupt>* aux = nullptr) : aux(aux) {}
		void operator ++ () { aux = aux->siguiente; }
		bool operator != (Iterador it) { return aux != it.aux; }
		NodoD<Corrupt>* operator* () { return aux; }
	};
	Iterador inicial() {
		return Iterador(inicio);
	};
	Iterador ultimo() {
		return Iterador(nullptr);
	};
	Arreglo_Corrupts();
	Arreglo_Corrupts(int n, Bitmap^ img_enemigo);
	void AgregarCorrupt(Bitmap^ img_enemigo);
	void Mover_Corrupts(Graphics^ g);
	void Graficar_Corrupts(Bitmap^ img_enemigo, Graphics^ g, Bitmap^ img_aliado);
	int retornar_cant();
	NodoD<Corrupt>* Retornar_corrupt(int pos);
	NodoD<Corrupt>* RecursivoRetornar(NodoD<Corrupt>* i, int pos, int s);
	NodoD<Corrupt>* Retornar_corruptIterador(int pos) {
		Iterador i = inicial();
		short id = 0;
		for (i; i != ultimo(); ++i, ++id) {
			if (id == pos)
				return *i;
		}

	}
	void Colision_Aliado_Corrupt(ArrAliados* arreglo_aliados, Bitmap^ img);

	void Eliminar_corrupt(int pos);
};