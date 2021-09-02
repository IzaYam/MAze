#include "Juego.h"
Juego::Juego()
{
	cant_vidas_personaje = 100;
	Transporto = false;
	aparecer_asesinos = false;
}
Juego::~Juego()
{
	delete jugador, lab;
}

void Juego::Iniciar(bool habilitarlectura,Graphics^ g, Bitmap^ img, Bitmap^ img_enemigo, Bitmap^ img_aliado, Bitmap^ img_puerta, Bitmap^ img_asesino) {
	auto leer_datos = [&]() {
		fstream archLec("datos.txt", ios::in);
		string nombre, dato;
		while (getline(archLec, nombre)) {
			stringstream linea(nombre);
			getline(linea, dato, ' ');
			cantCorrupts = stoi(dato);
			getline(linea, dato, ' ');
			cantAssassins = stoi(dato);
			getline(linea, dato, ' ');
			cant_vidas_personaje = stoi(dato);

		}
		archLec.close();
	};
	if (habilitarlectura) {
		leer_datos();
	}
	else {
		cantAliados = 7;
		cantCorrupts = cantAliados * 0.40;
		cantAssassins = cantAliados * 0.60;
	}

	puertita = new Puerta(1060, 380, img_puerta);
	portal = new Puerta(1, 380, img_puerta);
	jugador = new Jugador(img);
	lab = new Laberinto();
	corrupts = new Arreglo_Corrupts(cantCorrupts, img_enemigo);
	aliados = new ArrAliados(g, img_aliado, cantAliados);
	Asesinos = new Arreglo_Assassins(cantAssassins, img_asesino);
	
	lab->Iniciar(g);
	cool_down_convo = clock();
}
void Juego::GuardarJuego() {
	ofstream arcEsc("datos.txt");
	arcEsc << corrupts->retornar_cant() << ' ' << Asesinos->retornar_cant() << ' ' << cant_vidas_personaje;
	arcEsc.close();

	//al presionar jugar, se guardan los datos de cada uno de los personajes en el archivo "datos.txt"
}
void Juego::Entrada_asesinos(Bitmap^ img_asesino) {
	aparecer_asesinos = true;

}
void Juego::MoverJugador(bool accion, Keys tecla)
{
	if (lab->retornar_cant() == 0) { // -->  1 + (2 + 6) --> 9 T
		int v = 5; //--> 2 T
		if (accion == true) // --> 1+ (5) → 6T
		{
			if (tecla == Keys::Up) // →   1 + 4 → 5T
			{
				if (choca->retornar_pared(0) == false && choca->retornar_j() != 0) { //→ 2 + (1)
					jugador->SetDY(-v); //--> 1 T
				}

				jugador->SetAccion(CaminarArriba); //--> 1T;
			}
			else if (tecla == Keys::Down) //--> 5T
			{
				if (choca->retornar_pared(2) == false && choca->retornar_j() != 420) { // →2T

					jugador->SetDY(v); // 1T
				}

				jugador->SetAccion(CaminarAbajo); // 1T
			}
			else if (tecla == Keys::Left) // --> 4T
			{
				if (choca->retornar_pared(3) == false) { // → 1 + (1)

					jugador->SetDX(-v); //--> 1T
				}
				jugador->SetAccion(CaminarIzquierda); // --> 1T
			}
			else if (tecla == Keys::Right) // 4T
			{
				if (choca->retornar_pared(1) == false) { // → 1 + (1)

					jugador->SetDX(v); //--> 1T
				}

				jugador->SetAccion(CaminarDerecha); //--> 1T
			}
			else if (tecla == Keys::Escape) { // --> 3T
				if (jugador->GetAccion() == CaminarArriba) // → 1 + (1)
					jugador->SetAccion(AtacarArriba); // → 1T
				else if (jugador->GetAccion() == CaminarAbajo) // → 1 + (1)
					jugador->SetAccion(AtacarAbajo);  // → 1T
				else if (jugador->GetAccion() == CaminarDerecha) // → 1 + (1)
					jugador->SetAccion(AtacarDerecha); // → 1T
				else if (jugador->GetAccion() == CaminarIzquierda) // → 1 + (1) 
					jugador->SetAccion(AtacarIzquierda); // → 1T


			}
		}
		else // 2 T
		{
			if (tecla == Keys::Up) // → 1 + (1)
				jugador->SetDY(0); // → 1T
			else if (tecla == Keys::Down) // → 1 + (1)
				jugador->SetDY(0); // → 1T
			else if (tecla == Keys::Left)  // → 1 + (1)
				jugador->SetDX(0); // → 1T
			else if (tecla == Keys::Right)  // → 1 + (1)		
				jugador->SetDX(0); // → 1T
		} 
	}

	// Tiempo detallado:9T  y  BIG (O): 1
}
void Juego::Dibujar(Graphics^ g, Bitmap^ img, Bitmap^ mapa, Bitmap^ img_enemigo, Bitmap^ img_aliado, Bitmap^ img_puerta, Bitmap^ img_asesino) {
	g->DrawImage(mapa, 0, 0);
	lab->Dibujar(g);
	choca = lab->colision(jugador->HitBox());
	portal->Dibujar(g, img_puerta);
	Informacion(g);
	puertita->Dibujar(g, img_puerta);
	jugador->Dibujar(g, img);
	if (aparecer_asesinos)
		Asesinos->Graficar_asesinos(img_asesino, g);
	corrupts->Graficar_Corrupts(img_enemigo, g, img_asesino);
	cout << corrupts->retornar_cant();
	aliados->Dibujar(g, img_aliado);


	reloj = clock();

}
void Juego::Mover(Graphics^ g, Bitmap^ img_aliado) {
	auto colision_portal = [&]() {
		Rectangle jug = jugador->Area();
		Rectangle puerta = portal->Area();
		if (jug.IntersectsWith(puerta)) {
			if (Transporto == false) {

				jugador->SetY(5);
				jugador->SetX(1060);
				Transporto = true;
			}
		}
	};
	auto colision_corr_jug = [&]() {
		Rectangle jug = jugador->Area();
		Rectangle enemigo;
		for (int i = 0; i < corrupts->retornar_cant(); i++)
		{
			enemigo = corrupts->Retornar_corrupt(i)->elemento.HitBox();
			if (jug.IntersectsWith(enemigo)) {
				corrupts->Retornar_corrupt(i);
				cant_vidas_personaje -= 10;
			}
		}
	};
	if (lab->retornar_cant() == 0) {
		jugador->Mover(g);
		corrupts->Mover_Corrupts(g);
		aliados->Mover(g, jugador->Area());
		corrupts->Colision_Aliado_Corrupt(aliados, img_aliado);
		colision_portal();
		colision_corr_jug();
		if (aparecer_asesinos) {
			Asesinos->Mover_asesinos(g);
			Asesinos->Colision_Jugador_Asesino(jugador->HitBox());
			if (Asesinos->Colision_Jugador_Asesino(jugador->HitBox()))
				cant_vidas_personaje -= 20;
		}
	}
}
void Juego::Informacion(Graphics^ g) {
	Font^ f = gcnew Font("Arial", 20);
	g->DrawString("Vidas: " + cant_vidas_personaje + "   Tiempo" + clock() / 1000, f, Brushes::Black, 1, 420);
}
bool Juego::Colision_Puerta_final() {
	bool finalizo = false;
	auto colision = [=, &finalizo] {
		Rectangle jug = jugador->Area();
		Rectangle puerta = puertita->Area();
		if (jug.IntersectsWith(puerta)) {
			finalizo = true;
		}
		return finalizo; };
	return colision();
}
bool Juego::Iniciar_Conversacion() {

	if (reloj - cool_down_convo >= 50000 && reloj - cool_down_convo <= 60000) {
		return true;
	}
	else
		return false;

}
bool Juego::Final_Juego_Perdio() {
	return (cant_vidas_personaje == 0);
}
void Juego::Mensaje_final_perdio(Graphics^ g) {
	Font^ f = gcnew Font("Arial", 20);
	g->DrawString("Lo siento jugador, no pudo atravesar el laberinto con vida. Gracias por jugar!", f, Brushes::White, 1, g->VisibleClipBounds.Height / 2);
}
void Juego::Mensaje_final_ganador(Graphics^ g) {
	Font^ f = gcnew Font("Arial", 20);
	g->DrawString("Jugador, Usted lucho contra los Corrupts y Assasins y vencio, Es un honor.\n Gracias por jugar!", f, Brushes::White, 1, g->VisibleClipBounds.Height / 2);
}