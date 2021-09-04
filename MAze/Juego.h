#pragma once
#include "Personaje.h"
#include "Laberinto.h"
#include "Corrupt.h"
#include "Arreglo_Corrupts.h"
#include "ArrAliados.h"
#include "Puerta.h"
#include "Arreglo_Assassins.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
class Juego
{
private:
	int cant_vidas_personaje;
	int cantAliados;
	int cantCorrupts;
	int cantAssassins;
	bool Transporto;
	int cool_down_convo;
	int reloj;
	bool aparecer_asesinos;
	fstream resume;
	Jugador* jugador;
	Laberinto* lab;
	Celda* choca;
	Celda* col_ene;
	Celda* Colision_siguiente;
	Arreglo_Corrupts* corrupts;
	ArrAliados* aliados;
	Puerta* puertita;
	Puerta* portal;
	Arreglo_Assassins* Asesinos;
public:
	Juego();
	~Juego();
	void Iniciar(bool habilitarlectura,Graphics^ g, Bitmap^ img, Bitmap^ img_enemigo, Bitmap^ img_aliado, Bitmap^ img_puerta, Bitmap^ img_asesino);
	void MoverJugador(bool accion, Keys tecla);
	void Dibujar(Graphics^ g, Bitmap^ img, Bitmap^ mapa, Bitmap^ img_enemigo, Bitmap^ img_aliado, Bitmap^ img_puerta, Bitmap^ img_asesino);
	void Mover(Graphics^ g, Bitmap^ img_aliado);
	void Informacion(Graphics^ g);
	bool Colision_Puerta_final();
	void Entrada_asesinos(Bitmap^ img_asesino);
	bool Iniciar_Conversacion();
	bool Final_Juego_Perdio();
	void Mensaje_final_perdio(Graphics^ g);
	void Mensaje_final_ganador(Graphics^ g);
	void GuardarJuego();

};