#pragma once

namespace RobotGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RobotGUI
	/// </summary>
	public ref class RobotGUI : public System::Windows::Forms::Form
	{
	public:
		RobotGUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RobotGUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  lstboxRobotOutput;
	protected:
	private: System::Windows::Forms::TextBox^  txtboxCommandIPAddress;
	private: System::Windows::Forms::TextBox^  txtboxTelemetryIPAddress;
	private: System::Windows::Forms::Label^  lblCommandSocketIPAddress;
	private: System::Windows::Forms::Label^  lblTelemetrySocketIPAddress;
	private: System::Windows::Forms::Button^  btnCommandSocketConnect;
	private: System::Windows::Forms::Button^  btnTelemetrySocketConnect;
	private: System::Windows::Forms::GroupBox^  grpboxCommandTypes;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RobotGUI::typeid));
			this->lstboxRobotOutput = (gcnew System::Windows::Forms::ListBox());
			this->txtboxCommandIPAddress = (gcnew System::Windows::Forms::TextBox());
			this->txtboxTelemetryIPAddress = (gcnew System::Windows::Forms::TextBox());
			this->lblCommandSocketIPAddress = (gcnew System::Windows::Forms::Label());
			this->lblTelemetrySocketIPAddress = (gcnew System::Windows::Forms::Label());
			this->btnCommandSocketConnect = (gcnew System::Windows::Forms::Button());
			this->btnTelemetrySocketConnect = (gcnew System::Windows::Forms::Button());
			this->grpboxCommandTypes = (gcnew System::Windows::Forms::GroupBox());
			this->SuspendLayout();
			// 
			// lstboxRobotOutput
			// 
			this->lstboxRobotOutput->FormattingEnabled = true;
			this->lstboxRobotOutput->Location = System::Drawing::Point(12, 320);
			this->lstboxRobotOutput->Name = L"lstboxRobotOutput";
			this->lstboxRobotOutput->Size = System::Drawing::Size(785, 134);
			this->lstboxRobotOutput->TabIndex = 0;
			// 
			// txtboxCommandIPAddress
			// 
			this->txtboxCommandIPAddress->Location = System::Drawing::Point(163, 26);
			this->txtboxCommandIPAddress->Name = L"txtboxCommandIPAddress";
			this->txtboxCommandIPAddress->Size = System::Drawing::Size(151, 20);
			this->txtboxCommandIPAddress->TabIndex = 1;
			// 
			// txtboxTelemetryIPAddress
			// 
			this->txtboxTelemetryIPAddress->Location = System::Drawing::Point(163, 62);
			this->txtboxTelemetryIPAddress->Name = L"txtboxTelemetryIPAddress";
			this->txtboxTelemetryIPAddress->Size = System::Drawing::Size(151, 20);
			this->txtboxTelemetryIPAddress->TabIndex = 2;
			// 
			// lblCommandSocketIPAddress
			// 
			this->lblCommandSocketIPAddress->AutoSize = true;
			this->lblCommandSocketIPAddress->Location = System::Drawing::Point(9, 29);
			this->lblCommandSocketIPAddress->Name = L"lblCommandSocketIPAddress";
			this->lblCommandSocketIPAddress->Size = System::Drawing::Size(148, 13);
			this->lblCommandSocketIPAddress->TabIndex = 3;
			this->lblCommandSocketIPAddress->Text = L"Command Socket IP Address:";
			// 
			// lblTelemetrySocketIPAddress
			// 
			this->lblTelemetrySocketIPAddress->AutoSize = true;
			this->lblTelemetrySocketIPAddress->Location = System::Drawing::Point(9, 65);
			this->lblTelemetrySocketIPAddress->Name = L"lblTelemetrySocketIPAddress";
			this->lblTelemetrySocketIPAddress->Size = System::Drawing::Size(147, 13);
			this->lblTelemetrySocketIPAddress->TabIndex = 4;
			this->lblTelemetrySocketIPAddress->Text = L"Telemetry Socket IP Address:";
			// 
			// btnCommandSocketConnect
			// 
			this->btnCommandSocketConnect->Location = System::Drawing::Point(348, 24);
			this->btnCommandSocketConnect->Name = L"btnCommandSocketConnect";
			this->btnCommandSocketConnect->Size = System::Drawing::Size(162, 23);
			this->btnCommandSocketConnect->TabIndex = 5;
			this->btnCommandSocketConnect->Text = L"Connect Command Socket";
			this->btnCommandSocketConnect->UseVisualStyleBackColor = true;
			// 
			// btnTelemetrySocketConnect
			// 
			this->btnTelemetrySocketConnect->Location = System::Drawing::Point(348, 60);
			this->btnTelemetrySocketConnect->Name = L"btnTelemetrySocketConnect";
			this->btnTelemetrySocketConnect->Size = System::Drawing::Size(162, 23);
			this->btnTelemetrySocketConnect->TabIndex = 6;
			this->btnTelemetrySocketConnect->Text = L"Connect Telemetry Socket";
			this->btnTelemetrySocketConnect->UseVisualStyleBackColor = true;
			// 
			// grpboxCommandTypes
			// 
			this->grpboxCommandTypes->Location = System::Drawing::Point(12, 108);
			this->grpboxCommandTypes->Name = L"grpboxCommandTypes";
			this->grpboxCommandTypes->Size = System::Drawing::Size(302, 135);
			this->grpboxCommandTypes->TabIndex = 7;
			this->grpboxCommandTypes->TabStop = false;
			this->grpboxCommandTypes->Text = L"Available Commands";
			// 
			// RobotGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(809, 471);
			this->Controls->Add(this->grpboxCommandTypes);
			this->Controls->Add(this->btnTelemetrySocketConnect);
			this->Controls->Add(this->btnCommandSocketConnect);
			this->Controls->Add(this->lblTelemetrySocketIPAddress);
			this->Controls->Add(this->lblCommandSocketIPAddress);
			this->Controls->Add(this->txtboxTelemetryIPAddress);
			this->Controls->Add(this->txtboxCommandIPAddress);
			this->Controls->Add(this->lstboxRobotOutput);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"RobotGUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"                                                                  Decepticon Comm"
				L"unication Software";
			this->TopMost = true;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
