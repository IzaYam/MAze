#include "ArrAliados.h"

ArrAliados::ArrAliados() {}
ArrAliados::ArrAliados(Graphics^ g, Bitmap^ aliados, int pcant)
{
	srand(time(NULL));
	cant_max = pcant;
	cant = 0;
	Aliados* Seguidor1 = new Aliados(70,0,aliados);
	Seguidores.push_back(Seguidor1);
	Aliados* Seguidor2 = new Aliados(0, 70, aliados);
	Seguidores.push_back(Seguidor2);
	
	for (int i = 0; i< pcant; i++) {
		int posIx = rand() % 1100;
		int posIy = rand() % 400;
		Insertar_Aliados(posIx, posIy, aliados);
	}
}
void ArrAliados::Insertar_Aliados(int px, int py, Bitmap^ aliados) {
	Aliados** aux = new Aliados * [cant];
	for (int i = 0; i < cant; i++)
		aux[i] = arreglo[i];
	arreglo = new Aliados * [cant + 1];
	for (int i = 0; i < cant; i++)
		arreglo[i] = aux[i];
	arreglo[cant] = new Aliados(px, py, aliados);
	cant++;
}
void ArrAliados::Eliminar_aliado(int pos) {
	Aliados** aux = new Aliados * [cant - 1];
	for (int i = 0; i < pos; i++)
		aux[i] = arreglo[i];
	for (int i = pos; i < cant - 1; i++)
		aux[i] = arreglo[i + 1];
	delete arreglo[pos];
	if (arreglo != nullptr)
		delete[] arreglo;
	arreglo = aux;
	cant--;
}
void ArrAliados::Dibujar(Graphics^ g, Bitmap^ aliados) {
	for (int i = 0; i < cant; i++)
	{
		arreglo[i]->Dibujar(g, aliados);
	}
	for (int i = 0; i < Seguidores.size(); i++)
	{
		Seguidores.at(i)->Dibujar(g, aliados);
	}
}
void ArrAliados::Mover(Graphics^ g, Rectangle jug)
{
	for (int i = 0; i < cant; i++)
	{
		
		arreglo[i]->MoveType1(g);
		
	}
	for (int i = 0; i < Seguidores.size(); i++)
	{
		Seguidores.at(i)->Mover(g);
	}
		Mover2(g, jug);
	
}
void ArrAliados::Mover2(Graphics^ g, Rectangle jug)
{
	if (Colision_Aliado_Jugador(jug) == false)
	{
		for (int i = 0; i < Seguidores.size(); i++) {

			if (jug.X < Seguidores.at(i)->GetX()) {
				Seguidores.at(i)->Cambiar_direccion(Caminar2Izquierda);
				Seguidores.at(i)->SetDX(-2);
				Seguidores.at(i)->SetDY(0);

			}
			if (jug.X > Seguidores.at(i)->GetX())
			{
				Seguidores.at(i)->Cambiar_direccion(Caminar2Derecha);
				Seguidores.at(i)->SetDX(2);
				Seguidores.at(i)->SetDY(0);
			}
			if (jug.Y < Seguidores.at(i)->GetY()) {
				Seguidores.at(i)->Cambiar_direccion(Caminar2Arriba);
				Seguidores.at(i)->SetDY(-2);
			}
			if (jug.Y > Seguidores.at(i)->GetY())
			{
				Seguidores.at(i)->Cambiar_direccion(Caminar2Abajo);
				Seguidores.at(i)->SetDY(2);
			}
		}
	}
	else {
		for (int i = 0; i < Seguidores.size(); i++)
		{
			Seguidores.at(i)->SetDY(0);
			Seguidores.at(i)->SetDX(0);
		}
	}
}
int ArrAliados::retornar_cant()
{
	return cant;
}
Aliados* ArrAliados::retornar_pos_aliado(int pos) {
	return arreglo[pos];
}
bool ArrAliados::Colision_Aliado_Jugador(Rectangle jugador)
{
	bool colision = false;
	Rectangle rect1, rect2;
	for (int i = 0; i < Seguidores.size(); i++)
	{
		rect1 = Rectangle(Seguidores.at(i)->Area());

		rect2 = Rectangle(jugador.X, jugador.Y, jugador.Width, jugador.Height);
		if (rect1.IntersectsWith(rect2))
		{
			colision = true;
		}
	}
	return colision;
}