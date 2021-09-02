#pragma once

using namespace System::Drawing;
class Celda
{
	int i, j; // i representa x y j representa y 
	int w;
	bool paredes[4] = { true,true,true,true }; 
	// top , right ,bottom left
	bool visitado = false; 
	/*visitado se vuelve true una vez el algoritmo pasa por su posicion
	(es para que no se repita)
	*/
public:
	Celda();
	Celda(int ax, int ay);
	Rectangle Area();
	void cambiar_pared(bool nuevo, int pos);
	
	bool retornar_visitado();
	void Cambiar_visitado(bool nuevo);
	int retornar_i();
	int retornar_j();
	bool retornar_pared(int pos);
	void Dibujar(Graphics^ g);
};

