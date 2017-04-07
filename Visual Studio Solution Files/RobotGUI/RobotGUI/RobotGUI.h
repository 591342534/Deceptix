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
	private: System::Windows::Forms::RadioButton^  rdioBtnSleep;
	private: System::Windows::Forms::RadioButton^  rdioBtnClaw;
	private: System::Windows::Forms::RadioButton^  rdioBtnArm;
	private: System::Windows::Forms::RadioButton^  rdioBtnDrive;
	private: System::Windows::Forms::TextBox^  txtboxCommandSocketPort;
	private: System::Windows::Forms::Label^  lblCommandSocketPort;
	private: System::Windows::Forms::Label^  lblTelemetrySocketPort;
	private: System::Windows::Forms::TextBox^  txtboxTelemetrySocketPort;
	private: System::Windows::Forms::GroupBox^  grpBoxCommandSocket;
	private: System::Windows::Forms::GroupBox^  grpBoxTelemetrySocket;
	private: System::Windows::Forms::ComboBox^  cmbBoxDirection;
	private: System::Windows::Forms::ComboBox^  cmbBoxDuration;
	private: System::Windows::Forms::Label^  lblDuration;
	private: System::Windows::Forms::Label^  lblDirection;
	private: System::Windows::Forms::Button^  btnSendCommand;



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
			this->rdioBtnDrive = (gcnew System::Windows::Forms::RadioButton());
			this->rdioBtnArm = (gcnew System::Windows::Forms::RadioButton());
			this->rdioBtnClaw = (gcnew System::Windows::Forms::RadioButton());
			this->rdioBtnSleep = (gcnew System::Windows::Forms::RadioButton());
			this->txtboxCommandSocketPort = (gcnew System::Windows::Forms::TextBox());
			this->lblCommandSocketPort = (gcnew System::Windows::Forms::Label());
			this->lblTelemetrySocketPort = (gcnew System::Windows::Forms::Label());
			this->txtboxTelemetrySocketPort = (gcnew System::Windows::Forms::TextBox());
			this->grpBoxCommandSocket = (gcnew System::Windows::Forms::GroupBox());
			this->grpBoxTelemetrySocket = (gcnew System::Windows::Forms::GroupBox());
			this->cmbBoxDirection = (gcnew System::Windows::Forms::ComboBox());
			this->cmbBoxDuration = (gcnew System::Windows::Forms::ComboBox());
			this->lblDirection = (gcnew System::Windows::Forms::Label());
			this->lblDuration = (gcnew System::Windows::Forms::Label());
			this->btnSendCommand = (gcnew System::Windows::Forms::Button());
			this->grpboxCommandTypes->SuspendLayout();
			this->grpBoxCommandSocket->SuspendLayout();
			this->grpBoxTelemetrySocket->SuspendLayout();
			this->SuspendLayout();
			// 
			// lstboxRobotOutput
			// 
			this->lstboxRobotOutput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lstboxRobotOutput->FormattingEnabled = true;
			this->lstboxRobotOutput->ItemHeight = 16;
			this->lstboxRobotOutput->Location = System::Drawing::Point(12, 529);
			this->lstboxRobotOutput->MultiColumn = true;
			this->lstboxRobotOutput->Name = L"lstboxRobotOutput";
			this->lstboxRobotOutput->ScrollAlwaysVisible = true;
			this->lstboxRobotOutput->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->lstboxRobotOutput->Size = System::Drawing::Size(583, 132);
			this->lstboxRobotOutput->TabIndex = 0;
			this->lstboxRobotOutput->TabStop = false;
			// 
			// txtboxCommandIPAddress
			// 
			this->txtboxCommandIPAddress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->txtboxCommandIPAddress->Location = System::Drawing::Point(238, 35);
			this->txtboxCommandIPAddress->MaxLength = 15;
			this->txtboxCommandIPAddress->Name = L"txtboxCommandIPAddress";
			this->txtboxCommandIPAddress->Size = System::Drawing::Size(151, 26);
			this->txtboxCommandIPAddress->TabIndex = 0;
			// 
			// txtboxTelemetryIPAddress
			// 
			this->txtboxTelemetryIPAddress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->txtboxTelemetryIPAddress->Location = System::Drawing::Point(234, 32);
			this->txtboxTelemetryIPAddress->MaxLength = 15;
			this->txtboxTelemetryIPAddress->Name = L"txtboxTelemetryIPAddress";
			this->txtboxTelemetryIPAddress->Size = System::Drawing::Size(151, 26);
			this->txtboxTelemetryIPAddress->TabIndex = 3;
			// 
			// lblCommandSocketIPAddress
			// 
			this->lblCommandSocketIPAddress->AutoSize = true;
			this->lblCommandSocketIPAddress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCommandSocketIPAddress->Location = System::Drawing::Point(10, 42);
			this->lblCommandSocketIPAddress->Name = L"lblCommandSocketIPAddress";
			this->lblCommandSocketIPAddress->Size = System::Drawing::Size(222, 20);
			this->lblCommandSocketIPAddress->TabIndex = 3;
			this->lblCommandSocketIPAddress->Text = L"Command Socket IP Address:";
			// 
			// lblTelemetrySocketIPAddress
			// 
			this->lblTelemetrySocketIPAddress->AutoSize = true;
			this->lblTelemetrySocketIPAddress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTelemetrySocketIPAddress->Location = System::Drawing::Point(10, 39);
			this->lblTelemetrySocketIPAddress->Name = L"lblTelemetrySocketIPAddress";
			this->lblTelemetrySocketIPAddress->Size = System::Drawing::Size(218, 20);
			this->lblTelemetrySocketIPAddress->TabIndex = 4;
			this->lblTelemetrySocketIPAddress->Text = L"Telemetry Socket IP Address:";
			// 
			// btnCommandSocketConnect
			// 
			this->btnCommandSocketConnect->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCommandSocketConnect->Location = System::Drawing::Point(412, 52);
			this->btnCommandSocketConnect->Name = L"btnCommandSocketConnect";
			this->btnCommandSocketConnect->Size = System::Drawing::Size(162, 34);
			this->btnCommandSocketConnect->TabIndex = 2;
			this->btnCommandSocketConnect->Text = L"Connect Command Socket";
			this->btnCommandSocketConnect->UseVisualStyleBackColor = true;
			this->btnCommandSocketConnect->Click += gcnew System::EventHandler(this, &RobotGUI::btnCommandSocketConnect_Click);
			// 
			// btnTelemetrySocketConnect
			// 
			this->btnTelemetrySocketConnect->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnTelemetrySocketConnect->Location = System::Drawing::Point(412, 52);
			this->btnTelemetrySocketConnect->Name = L"btnTelemetrySocketConnect";
			this->btnTelemetrySocketConnect->Size = System::Drawing::Size(162, 34);
			this->btnTelemetrySocketConnect->TabIndex = 6;
			this->btnTelemetrySocketConnect->TabStop = false;
			this->btnTelemetrySocketConnect->Text = L"Connect Telemetry Socket";
			this->btnTelemetrySocketConnect->UseVisualStyleBackColor = true;
			// 
			// grpboxCommandTypes
			// 
			this->grpboxCommandTypes->Controls->Add(this->btnSendCommand);
			this->grpboxCommandTypes->Controls->Add(this->lblDuration);
			this->grpboxCommandTypes->Controls->Add(this->lblDirection);
			this->grpboxCommandTypes->Controls->Add(this->cmbBoxDuration);
			this->grpboxCommandTypes->Controls->Add(this->cmbBoxDirection);
			this->grpboxCommandTypes->Controls->Add(this->rdioBtnSleep);
			this->grpboxCommandTypes->Controls->Add(this->rdioBtnClaw);
			this->grpboxCommandTypes->Controls->Add(this->rdioBtnArm);
			this->grpboxCommandTypes->Controls->Add(this->rdioBtnDrive);
			this->grpboxCommandTypes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->grpboxCommandTypes->Location = System::Drawing::Point(12, 287);
			this->grpboxCommandTypes->Name = L"grpboxCommandTypes";
			this->grpboxCommandTypes->Size = System::Drawing::Size(583, 236);
			this->grpboxCommandTypes->TabIndex = 7;
			this->grpboxCommandTypes->TabStop = false;
			this->grpboxCommandTypes->Text = L"Command Selection";
			this->grpboxCommandTypes->Enter += gcnew System::EventHandler(this, &RobotGUI::grpboxCommandTypes_Enter);
			// 
			// rdioBtnDrive
			// 
			this->rdioBtnDrive->AutoSize = true;
			this->rdioBtnDrive->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rdioBtnDrive->Location = System::Drawing::Point(14, 46);
			this->rdioBtnDrive->Name = L"rdioBtnDrive";
			this->rdioBtnDrive->Size = System::Drawing::Size(63, 24);
			this->rdioBtnDrive->TabIndex = 5;
			this->rdioBtnDrive->TabStop = true;
			this->rdioBtnDrive->Text = L"Drive";
			this->rdioBtnDrive->UseVisualStyleBackColor = true;
			// 
			// rdioBtnArm
			// 
			this->rdioBtnArm->AutoSize = true;
			this->rdioBtnArm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rdioBtnArm->Location = System::Drawing::Point(346, 46);
			this->rdioBtnArm->Name = L"rdioBtnArm";
			this->rdioBtnArm->Size = System::Drawing::Size(56, 24);
			this->rdioBtnArm->TabIndex = 7;
			this->rdioBtnArm->TabStop = true;
			this->rdioBtnArm->Text = L"Arm";
			this->rdioBtnArm->UseVisualStyleBackColor = true;
			// 
			// rdioBtnClaw
			// 
			this->rdioBtnClaw->AutoSize = true;
			this->rdioBtnClaw->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rdioBtnClaw->Location = System::Drawing::Point(167, 46);
			this->rdioBtnClaw->Name = L"rdioBtnClaw";
			this->rdioBtnClaw->Size = System::Drawing::Size(61, 24);
			this->rdioBtnClaw->TabIndex = 6;
			this->rdioBtnClaw->TabStop = true;
			this->rdioBtnClaw->Text = L"Claw";
			this->rdioBtnClaw->UseVisualStyleBackColor = true;
			// 
			// rdioBtnSleep
			// 
			this->rdioBtnSleep->AutoSize = true;
			this->rdioBtnSleep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rdioBtnSleep->Location = System::Drawing::Point(502, 46);
			this->rdioBtnSleep->Name = L"rdioBtnSleep";
			this->rdioBtnSleep->Size = System::Drawing::Size(68, 24);
			this->rdioBtnSleep->TabIndex = 8;
			this->rdioBtnSleep->TabStop = true;
			this->rdioBtnSleep->Text = L"Sleep";
			this->rdioBtnSleep->UseVisualStyleBackColor = true;
			// 
			// txtboxCommandSocketPort
			// 
			this->txtboxCommandSocketPort->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->txtboxCommandSocketPort->Location = System::Drawing::Point(238, 72);
			this->txtboxCommandSocketPort->MaxLength = 5;
			this->txtboxCommandSocketPort->Name = L"txtboxCommandSocketPort";
			this->txtboxCommandSocketPort->Size = System::Drawing::Size(151, 26);
			this->txtboxCommandSocketPort->TabIndex = 1;
			// 
			// lblCommandSocketPort
			// 
			this->lblCommandSocketPort->AutoSize = true;
			this->lblCommandSocketPort->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCommandSocketPort->Location = System::Drawing::Point(35, 77);
			this->lblCommandSocketPort->Name = L"lblCommandSocketPort";
			this->lblCommandSocketPort->Size = System::Drawing::Size(173, 20);
			this->lblCommandSocketPort->TabIndex = 9;
			this->lblCommandSocketPort->Text = L"Command Socket Port:";
			// 
			// lblTelemetrySocketPort
			// 
			this->lblTelemetrySocketPort->AutoSize = true;
			this->lblTelemetrySocketPort->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTelemetrySocketPort->Location = System::Drawing::Point(35, 76);
			this->lblTelemetrySocketPort->Name = L"lblTelemetrySocketPort";
			this->lblTelemetrySocketPort->Size = System::Drawing::Size(169, 20);
			this->lblTelemetrySocketPort->TabIndex = 11;
			this->lblTelemetrySocketPort->Text = L"Telemetry Socket Port:";
			// 
			// txtboxTelemetrySocketPort
			// 
			this->txtboxTelemetrySocketPort->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->txtboxTelemetrySocketPort->Location = System::Drawing::Point(234, 69);
			this->txtboxTelemetrySocketPort->MaxLength = 5;
			this->txtboxTelemetrySocketPort->Name = L"txtboxTelemetrySocketPort";
			this->txtboxTelemetrySocketPort->Size = System::Drawing::Size(151, 26);
			this->txtboxTelemetrySocketPort->TabIndex = 4;
			// 
			// grpBoxCommandSocket
			// 
			this->grpBoxCommandSocket->Controls->Add(this->lblCommandSocketIPAddress);
			this->grpBoxCommandSocket->Controls->Add(this->txtboxCommandIPAddress);
			this->grpBoxCommandSocket->Controls->Add(this->lblCommandSocketPort);
			this->grpBoxCommandSocket->Controls->Add(this->btnCommandSocketConnect);
			this->grpBoxCommandSocket->Controls->Add(this->txtboxCommandSocketPort);
			this->grpBoxCommandSocket->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->grpBoxCommandSocket->Location = System::Drawing::Point(12, 12);
			this->grpBoxCommandSocket->Name = L"grpBoxCommandSocket";
			this->grpBoxCommandSocket->Size = System::Drawing::Size(583, 122);
			this->grpBoxCommandSocket->TabIndex = 12;
			this->grpBoxCommandSocket->TabStop = false;
			this->grpBoxCommandSocket->Text = L"Command Socket Metrics";
			// 
			// grpBoxTelemetrySocket
			// 
			this->grpBoxTelemetrySocket->Controls->Add(this->lblTelemetrySocketIPAddress);
			this->grpBoxTelemetrySocket->Controls->Add(this->txtboxTelemetryIPAddress);
			this->grpBoxTelemetrySocket->Controls->Add(this->btnTelemetrySocketConnect);
			this->grpBoxTelemetrySocket->Controls->Add(this->txtboxTelemetrySocketPort);
			this->grpBoxTelemetrySocket->Controls->Add(this->lblTelemetrySocketPort);
			this->grpBoxTelemetrySocket->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->grpBoxTelemetrySocket->Location = System::Drawing::Point(12, 152);
			this->grpBoxTelemetrySocket->Name = L"grpBoxTelemetrySocket";
			this->grpBoxTelemetrySocket->Size = System::Drawing::Size(583, 119);
			this->grpBoxTelemetrySocket->TabIndex = 13;
			this->grpBoxTelemetrySocket->TabStop = false;
			this->grpBoxTelemetrySocket->Text = L"Telemetry Socket Metrics";
			// 
			// cmbBoxDirection
			// 
			this->cmbBoxDirection->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cmbBoxDirection->FormattingEnabled = true;
			this->cmbBoxDirection->Items->AddRange(gcnew cli::array< System::Object^  >(11) {
				L"---", L"Forward", L"Backward", L"Right",
					L"Left", L"---", L"Up", L"Down", L"---", L"Open", L"Close"
			});
			this->cmbBoxDirection->Location = System::Drawing::Point(51, 114);
			this->cmbBoxDirection->Name = L"cmbBoxDirection";
			this->cmbBoxDirection->Size = System::Drawing::Size(153, 28);
			this->cmbBoxDirection->TabIndex = 9;
			// 
			// cmbBoxDuration
			// 
			this->cmbBoxDuration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cmbBoxDuration->FormattingEnabled = true;
			this->cmbBoxDuration->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"0", L"1", L"2", L"3", L"4", L"5" });
			this->cmbBoxDuration->Location = System::Drawing::Point(374, 114);
			this->cmbBoxDuration->Name = L"cmbBoxDuration";
			this->cmbBoxDuration->Size = System::Drawing::Size(153, 28);
			this->cmbBoxDuration->TabIndex = 10;
			// 
			// lblDirection
			// 
			this->lblDirection->AutoSize = true;
			this->lblDirection->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDirection->Location = System::Drawing::Point(87, 86);
			this->lblDirection->Name = L"lblDirection";
			this->lblDirection->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lblDirection->Size = System::Drawing::Size(81, 20);
			this->lblDirection->TabIndex = 10;
			this->lblDirection->Text = L"Direction";
			// 
			// lblDuration
			// 
			this->lblDuration->AutoSize = true;
			this->lblDuration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDuration->Location = System::Drawing::Point(408, 86);
			this->lblDuration->Name = L"lblDuration";
			this->lblDuration->Size = System::Drawing::Size(78, 20);
			this->lblDuration->TabIndex = 11;
			this->lblDuration->Text = L"Duration";
			// 
			// btnSendCommand
			// 
			this->btnSendCommand->Location = System::Drawing::Point(154, 163);
			this->btnSendCommand->Name = L"btnSendCommand";
			this->btnSendCommand->Size = System::Drawing::Size(248, 57);
			this->btnSendCommand->TabIndex = 12;
			this->btnSendCommand->Text = L"Submit Command";
			this->btnSendCommand->UseVisualStyleBackColor = true;
			// 
			// RobotGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(605, 673);
			this->Controls->Add(this->grpBoxTelemetrySocket);
			this->Controls->Add(this->grpBoxCommandSocket);
			this->Controls->Add(this->grpboxCommandTypes);
			this->Controls->Add(this->lstboxRobotOutput);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"RobotGUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Decepticon Communication Software";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &RobotGUI::RobotGUI_Load);
			this->grpboxCommandTypes->ResumeLayout(false);
			this->grpboxCommandTypes->PerformLayout();
			this->grpBoxCommandSocket->ResumeLayout(false);
			this->grpBoxCommandSocket->PerformLayout();
			this->grpBoxTelemetrySocket->ResumeLayout(false);
			this->grpBoxTelemetrySocket->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void grpboxCommandTypes_Enter(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void RobotGUI_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btnCommandSocketConnect_Click(System::Object^  sender, System::EventArgs^  e) {
	

}
};
}
