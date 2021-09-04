#include "Laberinto.h"
Laberinto::Laberinto() {
}
void Laberinto::Iniciar(Graphics^ g) {
	cols = 16;
	rows = 6;
	Celda* auxiliar;
	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++)
		{
			auxiliar = new Celda(i, j);
			grid.push_back(auxiliar);
		}
	}
	current = grid.at(0);
}
void Laberinto::Dibujar(Graphics^ g) {
	for (int i = 0; i < grid.size(); i++) {
		grid.at(i)->Dibujar(g);
		//g->DrawRectangle(Pens::Red, grid2[i]->Area());
	}
	current->Cambiar_visitado(true);
	//PASO 1
	Celda* next = Verificar_Vecino(current);
	if (next) {
		next->Cambiar_visitado(true);
		//PASO 2
		stack.push_back(current);
		//PASE 3
		Remover_Pared(current, next);
		//PASO 4
		current = next;
	}
	else if ((stack.size() > 0)) {
		Celda* aux = stack.back();
		stack.pop_back();
		current = aux;
	}
//	Dibujar_Current(g);
}
Celda* Laberinto::colision(Rectangle per) {
	for (int i = 0; i < grid.size(); i++) {

		if (grid.at(i)->Area().IntersectsWith(per)) {
			return grid.at(i);
		}
	}
}
Celda* Laberinto::Rectornar_celda(int i) {
	if (grid.at(i) != nullptr) {
		return grid.at(i);
	}
}
Celda* Laberinto::Verificar_Vecino(Celda* celda) {
	srand(time(NULL));
	int i = celda->retornar_i();
	int j = celda->retornar_j();
	/*Aca se toma de referencia el current
	arriba, derecha, abajo e izquierda representan los vecinos el indice que se obtiene
	por la funcion index
	*/
	vector<Celda*>vecinos;
	Celda* arriba = grid[index(i, j - 1)];
	Celda* derecha = grid[index(i + 1, j)];
	Celda* Abajo = grid[index(i, j + 1)];
	Celda* Izquierda = grid[index(i - 1, j)];
	// Si el vecino existe y no ha sido visitado aun pues se agrega al arreglo de vecinos
	if (arriba && (arriba->retornar_visitado() == false)) {
		vecinos.push_back(arriba);
	}
	if (derecha && (derecha->retornar_visitado() == false)) {

		vecinos.push_back(derecha);
	}
	if (Abajo && (Abajo->retornar_visitado() == false)) {

		vecinos.push_back(Abajo);
	}
	if (Izquierda && (Izquierda->retornar_visitado() == false)) {

		vecinos.push_back(Izquierda);
	}
	if (vecinos.size() > 0) {
		int r = rand() % (vecinos.size());
		return vecinos[r];
		//Si existe almenos un vecino, se escoge un vecino r que es aleatorio a el numero de vecinos 
		/// pueden ir de 1 a 3 creo 
	}
	else {
		//sino se  retorna un undefinied
		return NULL;
	}
}
int Laberinto::index(int i, int  j) {
	if (i < 0 || j < 0 || i> cols - 1 || j > rows - 1) {
		return NULL;
	}
	return  i + j * cols;
}
void Laberinto::Remover_Pared(Celda* a, Celda* b) {
	int x = a->retornar_i() - b->retornar_i();
	if (x == 1) {
		a->cambiar_pared(false, 3);
		b->cambiar_pared(false, 1);
	}
	else if (x == -1) {
		a->cambiar_pared(false, 1);
		b->cambiar_pared(false, 3);
	}
	int y = a->retornar_j() - b->retornar_j();
	if (y == 1) {
		a->cambiar_pared(false, 0);
		b->cambiar_pared(false, 2);
	}
	else if (y == -1) {
		a->cambiar_pared(false, 2);
		b->cambiar_pared(false, 0);
	}
}
int Laberinto::retornar_cant() {
	return stack.size();
}
void Laberinto::Dibujar_Current(Graphics^ g) {
	int x = current->retornar_i();
	int y = current->retornar_j();
	g->DrawRectangle(Pens::Blue, x * 70, y * 70, 70, 70);
}