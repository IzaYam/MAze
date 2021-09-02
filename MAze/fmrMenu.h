#pragma once
#include "fmrMapaJuego.h"
namespace MAze {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
		{
			InitializeComponent();
			img_fondo = gcnew Bitmap("img/Inicio.png");
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
			delete img_fondo;
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Timer^ Inicio;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;


	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>

		Bitmap^ img_fondo;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->Inicio = (gcnew System::Windows::Forms::Timer(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::SaddleBrown;
			this->button1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::Control;
			this->button1->Location = System::Drawing::Point(255, 391);
			this->button1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(205, 70);
			this->button1->TabIndex = 0;
			this->button1->Text = L"JUGAR";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm1::button1_Click);
			// 
			// Inicio
			// 
			this->Inicio->Enabled = true;
			this->Inicio->Tick += gcnew System::EventHandler(this, &MyForm1::Inicio_Tick);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::SaddleBrown;
			this->button2->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::SystemColors::Control;
			this->button2->Location = System::Drawing::Point(591, 391);
			this->button2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(205, 70);
			this->button2->TabIndex = 1;
			this->button2->Text = L"SALIR";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm1::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::OrangeRed;
			this->button3->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::SystemColors::Control;
			this->button3->Location = System::Drawing::Point(316, 482);
			this->button3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(431, 70);
			this->button3->TabIndex = 2;
			this->button3->Text = L"JUGAR PARTIDA GUARDADA";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm1::button3_Click);
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1013, 585);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MyForm1";
			this->Text = L"MyForm1";
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm^ juego = gcnew MyForm(false);
		juego->ShowDialog();
	}

	private: System::Void Inicio_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = CreateGraphics();
		g->DrawImage(img_fondo, 0, 0);
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	MyForm^ juego = gcnew MyForm(true);
	juego->ShowDialog();
}
private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}