/*
 * PVZ Cheat (Interface)
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

#include "pvzCheatGraphic.h" // " " used to include programmer-defined header files
#include <Windows.h>         // < > used to include standard library header files
#include <stdarg.h>
#include <stdio.h>

using namespace System;
using namespace System::Windows::Forms;

// the main function is used to display the interface of the cheater
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    PVZCheat::MyForm form;
    Application::Run(% form);

    return 0;
}
