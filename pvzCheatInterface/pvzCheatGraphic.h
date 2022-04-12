/*
 * PVZ Cheat
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

#pragma once

#include "pvzCheatUtil.h"
#include <Windows.h>
#include <msclr/marshal_cppstd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

namespace PVZCheat
{

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace std;

/// <summary>
/// Summary for MyForm
/// </summary>
public
ref class MyForm : public System::Windows::Forms::Form
{
  public:
    static HANDLE hProcess; // process handle of the game

  public:
    MyForm(void)
    {
        InitializeComponent();
        pvzCheatUtil::openProcess();
        //
        // TODO: Add the constructor code here
        //
    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~MyForm()
    {
        if (components)
        {
            delete components;
        }
    }

  private:
    System::Windows::Forms::TextBox ^ textBoxSunNum;

  protected:
  private:
    System::Windows::Forms::Label ^ textLabelSunNum;

  private:
    System::Windows::Forms::Button ^ buttonGetSunNum;

  private:
    System::Windows::Forms::Button ^ buttonChangeSunNum;

  private:
    System::Windows::Forms::CheckBox ^ checkBoxNoCD;

  protected:
  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
        this->textBoxSunNum = (gcnew System::Windows::Forms::TextBox());
        this->textLabelSunNum = (gcnew System::Windows::Forms::Label());
        this->buttonGetSunNum = (gcnew System::Windows::Forms::Button());
        this->buttonChangeSunNum = (gcnew System::Windows::Forms::Button());
        this->checkBoxNoCD = (gcnew System::Windows::Forms::CheckBox());
        this->SuspendLayout();
        //
        // textBoxSunNum
        //
        this->textBoxSunNum->Font =
            (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular,
                                         System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
        this->textBoxSunNum->Location = System::Drawing::Point(23, 58);
        this->textBoxSunNum->Name = L"textBoxSunNum";
        this->textBoxSunNum->Size = System::Drawing::Size(100, 29);
        this->textBoxSunNum->TabIndex = 0;
        this->textBoxSunNum->Text = L"\?\?\?";
        //
        // textLabelSunNum
        //
        this->textLabelSunNum->AutoSize = true;
        this->textLabelSunNum->Font =
            (gcnew System::Drawing::Font(L"Consolas", 11, System::Drawing::FontStyle::Regular,
                                         System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
        this->textLabelSunNum->Location = System::Drawing::Point(9, 15);
        this->textLabelSunNum->Name = L"textLabelSunNum";
        this->textLabelSunNum->Size = System::Drawing::Size(132, 26);
        this->textLabelSunNum->TabIndex = 1;
        this->textLabelSunNum->Text = L"Sun Number";
        //
        // buttonGetSunNum
        //
        this->buttonGetSunNum->Font =
            (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular,
                                         System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
        this->buttonGetSunNum->Location = System::Drawing::Point(147, 12);
        this->buttonGetSunNum->Name = L"buttonGetSunNum";
        this->buttonGetSunNum->Size = System::Drawing::Size(90, 34);
        this->buttonGetSunNum->TabIndex = 2;
        this->buttonGetSunNum->Text = L"Get";
        this->buttonGetSunNum->UseVisualStyleBackColor = true;
        this->buttonGetSunNum->Click += gcnew System::EventHandler(this, &MyForm::buttonGetSunNum_Click);
        //
        // buttonChangeSunNum
        //
        this->buttonChangeSunNum->Font =
            (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular,
                                         System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
        this->buttonChangeSunNum->Location = System::Drawing::Point(147, 58);
        this->buttonChangeSunNum->Name = L"buttonChangeSunNum";
        this->buttonChangeSunNum->Size = System::Drawing::Size(90, 34);
        this->buttonChangeSunNum->TabIndex = 3;
        this->buttonChangeSunNum->Text = L"Change";
        this->buttonChangeSunNum->UseVisualStyleBackColor = true;
        this->buttonChangeSunNum->Click += gcnew System::EventHandler(this, &MyForm::buttonChangeSunNum_Click);
        //
        // checkBoxNoCD
        //
        this->checkBoxNoCD->AutoSize = true;
        this->checkBoxNoCD->Font =
            (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Regular,
                                         System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
        this->checkBoxNoCD->Location = System::Drawing::Point(16, 108);
        this->checkBoxNoCD->Name = L"checkBoxNoCD";
        this->checkBoxNoCD->Size = System::Drawing::Size(168, 27);
        this->checkBoxNoCD->TabIndex = 4;
        this->checkBoxNoCD->Text = L"Plants No CD";
        this->checkBoxNoCD->UseVisualStyleBackColor = true;
        this->checkBoxNoCD->Click += gcnew System::EventHandler(this, &MyForm::checkBoxNoCD_Click);
        //
        // MyForm
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(250, 147);
        this->Controls->Add(this->checkBoxNoCD);
        this->Controls->Add(this->buttonChangeSunNum);
        this->Controls->Add(this->buttonGetSunNum);
        this->Controls->Add(this->textLabelSunNum);
        this->Controls->Add(this->textBoxSunNum);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
        this->Name = L"MyForm";
        this->Text = L"PVZ Cheat";
        this->ResumeLayout(false);
        this->PerformLayout();
    }
#pragma endregion

  private:
    System::Void buttonGetSunNum_Click(System::Object ^ sender, System::EventArgs ^ e)
    {
        DWORD sunNum = pvzCheatUtil::readSunNum();
        textBoxSunNum->Text = sunNum.ToString();
    }

  private:
    System::Void buttonChangeSunNum_Click(System::Object ^ sender, System::EventArgs ^ e)
    {
        String ^ sunNum = textBoxSunNum->Text;
        std::string converted_sunNum = msclr::interop::marshal_as<std::string>(sunNum);
        int value = 0;
        try
        {
            value = Convert::ToInt32(textBoxSunNum->Text);
        }
        catch (...)
        {
            printf("Error");
        }
        DWORD a = value;
        pvzCheatUtil::changeSunNum(&a);
    }

  private:
    System::Void checkBoxNoCD_Click(System::Object ^ sender, System::EventArgs ^ e)
    {
        if (checkBoxNoCD->Checked)
        {
            pvzCheatUtil::noCD(true);
        }
        else
        {
            pvzCheatUtil::noCD(false);
        }
    }
};
} // namespace PVZCheat
