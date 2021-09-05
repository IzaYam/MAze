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

	
	Arreglo_Corrupts();
	Arreglo_Corrupts(int n, Bitmap^ img_enemigo);
	void AgregarCorrupt(Bitmap^ img_enemigo);
	void Mover_Corrupts(Graphics^ g);
	void Graficar_Corrupts(Bitmap^ img_enemigo, Graphics^ g, Bitmap^ img_aliado);
	int retornar_cant();
	NodoD<Corrupt>* Retornar_corrupt(int pos);
	NodoD<Corrupt>* RecursivoRetornar(NodoD<Corrupt>* i, int pos, int s);
	
	void Colision_Aliado_Corrupt(ArrAliados* arreglo_aliados, Bitmap^ img);

};