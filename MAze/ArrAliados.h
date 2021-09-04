#pragma once
#include "Aliados.h"
#include <time.h>
#include <vector>
using namespace std;
class ArrAliados
{
private:
	Aliados** arreglo;
	vector<Aliados*> Seguidores;
	int cant;
	int cant_max;
	int posIx, posIy;

public:
	ArrAliados();
	ArrAliados(Graphics^ g, Bitmap^ aliados, int pcant);
	void Insertar_Aliados(int px, int py, Bitmap^ aliados);
	void Dibujar(Graphics^ g, Bitmap^ aliados);
	void Mover(Graphics^ g, Rectangle jug);
	void Mover2(Graphics^ g, Rectangle jug);
	int retornar_cant();
	void Eliminar_aliado(int pos);
	Aliados* retornar_pos_aliado(int pos);
	bool Colision_Aliado_Jugador(Rectangle jugador);
	
	Aliados* retornar_seguidor(int pos);
};
