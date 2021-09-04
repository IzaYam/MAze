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
	//auto leer_datos = [&]() {
	if (habilitarlectura) {
		fstream resume("LastGame.txt", ios::in);
		int i = 0;
		if (resume.is_open()) {
			string nombre, dato;
			while (getline(resume, nombre)) {
				stringstream linea(nombre);
				if (i == 0) {
					jugador = new Jugador(img, i, i);
					getline(linea, dato, ' '); jugador->SetX(stoi(dato));
					getline(linea, dato, ' '); jugador->SetY(stoi(dato)); 
					//string pos; stringstream strPosAss(nombre);
					//getline(strPosAss, pos, ' '); int num = atoi(pos.c_str());
					//getline(strPosAss, pos, ' '); int num2 = atoi(pos.c_str());
					//jugador = new Jugador(img, num, num2);
				}
				if (i == 1) {
					getline(linea, dato, ' ');
					cantAliados = stoi(dato);
				}
				if (i == 2) {
					getline(linea, dato, ' ');
					cantCorrupts = stoi(dato);
				}
				if (i == 3) {
					getline(linea, dato, ' ');
					cantAssassins = stoi(dato);
				}
				if (i == 4) {
					getline(linea, dato, ' ');
					cant_vidas_personaje = stoi(dato);
				}
				//if (i >= 5 && i <= aliados->retornar_cant() + 4) {
				//	aliados->retornar_pos_aliado(i)->SetX(1);
				//}
				++i;
			}
			resume.close();
		}
		//};
	}
	//if (habilitarlectura) {
		//leer_datos();
	//}
	else{
		cantAliados = 7;
		cantCorrupts = cantAliados * 0.40;
		cantAssassins = cantAliados * 0.60;
		jugador = new Jugador(img,1,1);
	}
	
	puertita = new Puerta(1060, 380, img_puerta);
	portal = new Puerta(1, 380, img_puerta);
	lab = new Laberinto();
	corrupts = new Arreglo_Corrupts(cantCorrupts, img_enemigo);
	aliados = new ArrAliados(g, img_aliado, cantAliados);
	Asesinos = new Arreglo_Assassins(cantAssassins, img_asesino);

	lab->Iniciar(g);
	cool_down_convo = clock();
}
void Juego::GuardarJuego() {
	fstream save("LastGame.txt", ios::out);
	//for (int i = 0; i < 6; ++i) { //guardar laberinto falta
		//for (int j = 0; j < 16; ++j) {
			
		//}
	//}
	save << jugador->GetX() << " " << jugador->GetY() << endl;
	save << aliados->retornar_cant()<<endl;
	save << corrupts->retornar_cant() << endl;
	save << Asesinos->retornar_cant() << endl;
	save << cant_vidas_personaje << endl;
	//for (int i = 0; i < aliados->retornar_cant(); ++i) {
	//	save << aliados->retornar_seguidor(i)->GetX() << " " << aliados->retornar_seguidor(i)->GetY() << endl;
	//}

	//Presiona A para guardar la partida
}
void Juego::Entrada_asesinos(Bitmap^ img_asesino) {
	aparecer_asesinos = true;

}
void Juego::MoverJugador(bool accion, Keys tecla)
{
	if (lab->retornar_cant() == 0) { 
		int v = 5; 
		if (accion == true) 
		{
			if (tecla == Keys::Up) 
			{
				if (choca->retornar_pared(0) == false && choca->retornar_j() != 0) { 
					jugador->SetDY(-v);
				}

				jugador->SetAccion(CaminarArriba); 
			}
			else if (tecla == Keys::Down)
			{
				if (choca->retornar_pared(2) == false && choca->retornar_j() != 420) {

					jugador->SetDY(v); 
				}

				jugador->SetAccion(CaminarAbajo); 
			}
			else if (tecla == Keys::Left) 
			{
				if (choca->retornar_pared(3) == false) { 

					jugador->SetDX(-v); 
				}
				jugador->SetAccion(CaminarIzquierda); 
			}
			else if (tecla == Keys::Right)
			{
				if (choca->retornar_pared(1) == false) {

					jugador->SetDX(v);
				}

				jugador->SetAccion(CaminarDerecha);
			}
			else if (tecla == Keys::Escape) { 
				if (jugador->GetAccion() == CaminarArriba) 
					jugador->SetAccion(AtacarArriba); 
				else if (jugador->GetAccion() == CaminarAbajo) 
					jugador->SetAccion(AtacarAbajo); 
				else if (jugador->GetAccion() == CaminarDerecha) 
					jugador->SetAccion(AtacarDerecha); 
				else if (jugador->GetAccion() == CaminarIzquierda) 
					jugador->SetAccion(AtacarIzquierda);

			}
			else if(tecla==Keys::A) GuardarJuego();
		}
		else 
		{
			if (tecla == Keys::Up) 
				jugador->SetDY(0); 
			else if (tecla == Keys::Down) 
				jugador->SetDY(0); 
			else if (tecla == Keys::Left)  
				jugador->SetDX(0); 
			else if (tecla == Keys::Right) 
				jugador->SetDX(0); 
		} 
	}

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
	g->DrawString("Vidas: " + cant_vidas_personaje , f, Brushes::Black, 1, 420);
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