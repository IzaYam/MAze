#pragma once
#include "Juego.h"
#include "Conversacion.h"
namespace MAze {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(bool habilitarjuego)
		{
			InitializeComponent();
			obj_juego = new Juego();
			img_mapa = gcnew Bitmap("img/Mapa_aumentado.png");
			img_jug = gcnew Bitmap("img/jugador.png");
			img_enemigo = gcnew Bitmap("img/corrupts.png");
			img_aliado = gcnew Bitmap("img/Aliados.png");
			img_puerta = gcnew Bitmap("img/caja.png");
			img_asesino = gcnew Bitmap("img/Assassins.png");
			this->habilitarjuego = habilitarjuego;
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete obj_juego, img_aliado, img_enemigo, img_jug, img_puerta,img_mapa;
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		Graphics^ g;
		BufferedGraphicsContext^ espacio;
		BufferedGraphics^ buffer;
		Juego* obj_juego;
		Bitmap^ img_jug;
		Bitmap^ img_mapa;
		Bitmap^ img_aliado;
		Bitmap^ img_enemigo;
	    Bitmap^ img_puerta;
		Bitmap^ img_asesino;
		int tiempo;
		bool habilitarjuego;
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1160, 459);
			this->Font = (gcnew System::Drawing::Font(L"MS PGothic", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		g = this->CreateGraphics();
		espacio = BufferedGraphicsManager::Current;
		buffer = espacio->Allocate(g, this->ClientRectangle);
		obj_juego->Mover(buffer->Graphics, img_aliado);
		obj_juego->Dibujar(buffer->Graphics, img_jug,img_mapa,img_enemigo, img_aliado,img_puerta,img_asesino);
		if (obj_juego->Colision_Puerta_final()) {
			buffer->Graphics->Clear(Color::Blue);
			obj_juego->Mensaje_final_ganador(buffer->Graphics);
			timer1->Enabled = false;
		}
		
		if (obj_juego->Iniciar_Conversacion()){
			timer1->Enabled = false;
			//Conversacion^ incio = gcnew Conversacion();
			//incio->ShowDialog();
		}
		if (obj_juego->Final_Juego_Perdio()) {
			buffer->Graphics->Clear(Color::Black);
			obj_juego->Mensaje_final_perdio(buffer->Graphics);
			timer1->Enabled = false;
		}
		buffer->Render(g);
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		
		obj_juego->MoverJugador(true, e->KeyCode);
		if (e->KeyCode == Keys::Escape) {
			timer1->Enabled = true;
		}
		if (e->KeyCode == Keys::Space) {
			obj_juego->Entrada_asesinos(img_asesino);
		}
		if (e->KeyCode == Keys::G) {
			obj_juego->GuardarJuego();
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		obj_juego->MoverJugador(false, e->KeyCode);
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = CreateGraphics();
		obj_juego->Iniciar(habilitarjuego,g, img_jug, img_enemigo, img_aliado, img_puerta, img_asesino);
	}
};
}
