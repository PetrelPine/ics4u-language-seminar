/*
 * PVZ Cheat
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

// declarations of functions
void hookProcess();
DWORD ReadMemory(DWORD placeHolder, ...);
void WriteMemory(void *, DWORD, ...);
DWORD readSunNum();
void changeSunNum(DWORD);
void noCD(boolean);

// global variables
static HANDLE hProcess; // process handle of the game

// main function
int main()
{
    // gain access to the game
    hookProcess();

    // read sun number
    DWORD dwSunNum = readSunNum();
    printf("Current sun number: %lu.\n", dwSunNum);

    // change sun number
    if (1)
    {
        // the new sun number that you want to change to
        DWORD dwSunNumNew = 2000;
        // printf("Please enter the new sun number:\n");
        // scanf("%lu", &dwSunNumNew);
        // printf("New sun number: %lu.\n", dwSunNumNew);
        changeSunNum(&dwSunNumNew);
    }

    // plants no CD
    boolean choiceNoCD = TRUE;
    // boolean choiceNoCD = FALSE;
    noCD(choiceNoCD);

    return 0;
}

// function to gain access to the game
void hookProcess()
{
    // find game process
    HWND hwnd = FindWindow(NULL, (LPCSTR) "Plants vs. Zombies");
    if (hwnd == NULL)
    {
        printf("ERROR: Cannot find window.\n");
        exit(-1); // exit program
    }
    else
        printf("SUCCESS: Window found.\n");

    // find game process ID
    DWORD dwPID = 0;
    GetWindowThreadProcessId(hwnd, (LPDWORD)&dwPID);
    if (dwPID == 0)
    {
        printf("ERROR: Cannot find process ID.\n");
        exit(-1); // exit program
    }
    else
        printf("SUCCESS: Process ID found.\n");

    // access game process
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
    if (hProcess == NULL)
    {
        printf("ERROR: Cannot open process.\n");
        exit(-1); // exit program
    }
    else
        printf("SUCCESS: Process opened.\n");
}

// function to read the value in a specific memory address
DWORD ReadMemory(DWORD placeHolder, ...)
{
    if (hProcess == NULL)
        return -1;

    DWORD lastAddress = 0;
    DWORD offset = 0;
    DWORD lastAddressValue = 0;

    va_list addresses;
    va_start(addresses, placeHolder);

    while ((offset = va_arg(addresses, DWORD)) != -1)
    {
        lastAddress = lastAddressValue + offset;
        if (0 == ReadProcessMemory(hProcess, (LPCVOID)lastAddress, &lastAddressValue, sizeof(DWORD), NULL))
        {
            printf("ERROR: ReadMemory failed, last address: %#lx.\n", lastAddress);
            exit(-1);
        }
    }

    va_end(addresses);

    return lastAddressValue;
}

// function to write a value into a specific memory address
void WriteMemory(void *valueToWrite, DWORD valueSize, ...)
{
    if (valueToWrite == NULL || valueSize == 0 || hProcess == NULL)
        return;

    DWORD lastAddress = 0;
    DWORD offset = 0;
    DWORD lastAddressValue = 0;

    va_list addresses;
    va_start(addresses, valueSize);

    while ((offset = va_arg(addresses, DWORD)) != -1)
    {
        lastAddress = lastAddressValue + offset;
        if (0 == ReadProcessMemory(hProcess, (LPCVOID)lastAddress, &lastAddressValue, sizeof(DWORD), NULL))
        {
            printf("ERROR: ReadMemory failed, last address: %#lx.\n", lastAddress);
            exit(-1);
        }
    }
    va_end(addresses);

    if (0 == WriteProcessMemory(hProcess, (LPVOID)lastAddress, valueToWrite, valueSize, NULL))
    {
        printf("ERROR: WriteMemory failed, last address: %#lx.\n", lastAddress);
        exit(-1);
    }
}

// function to read the current sun number in the game
DWORD readSunNum()
{
    DWORD dwSunBaseAddress = 0x6A9EC0; // base address
    DWORD dwSunFirstOffset = 0x768;    // first offset address
    DWORD dwSunSecondOffset = 0x5560;  // second offset address

    DWORD dwSunNum = 0; // store sun number
    dwSunNum = ReadMemory(-1, dwSunBaseAddress, dwSunFirstOffset, dwSunSecondOffset, -1);

    return dwSunNum;
}

// function to change the current sun number in the game
void changeSunNum(DWORD *dwSunNumNew)
{
    DWORD dwSunBaseAddress = 0x6A9EC0; // base address
    DWORD dwSunFirstOffset = 0x768;    // first offset address
    DWORD dwSunSecondOffset = 0x5560;  // second offset address

    // write new sun number
    WriteMemory(dwSunNumNew, sizeof(dwSunNumNew), dwSunBaseAddress, dwSunFirstOffset, dwSunSecondOffset, -1);
    // print message
    printf("Sun number is changed to %lu.\n", *dwSunNumNew);
}

// function to switch the CD status of the plants in the game (CD is on / CD is off)
void noCD(boolean choice)
{
    DWORD dwCDBaseAddress = 0x487296;
    BYTE dataNoCDOn[] = {0x90, 0x90};
    BYTE dataNoCDOff[] = {0x7E, 0x14};

    // test before
    DWORD dwCDBaseValue1 = 0;
    DWORD dwCDBaseValue2 = 0;

    dwCDBaseValue1 = ReadMemory(-1, dwCDBaseAddress, -1);
    dwCDBaseValue2 = ReadMemory(-1, dwCDBaseAddress + sizeof(BYTE), -1);

    printf("dwCDBaseValue1 before: %#lx.\n", dwCDBaseValue1);
    printf("dwCDBaseValue2 before: %#lx.\n", dwCDBaseValue2);

    if (choice)
    {
        WriteMemory(dataNoCDOn, sizeof(dataNoCDOff), dwCDBaseAddress, -1);
        printf("Plants no CD is ON.\n");
    }
    else
    {
        WriteMemory(dataNoCDOff, sizeof(dataNoCDOn), dwCDBaseAddress, -1);
        printf("Plants no CD is OFF.\n");
    }

    // test after
    DWORD dwCDBaseValue3 = 0;
    DWORD dwCDBaseValue4 = 0;

    dwCDBaseValue3 = ReadMemory(-1, dwCDBaseAddress, -1);
    dwCDBaseValue4 = ReadMemory(-1, dwCDBaseAddress + sizeof(BYTE), -1);

    printf("dwCDBaseValue1 after: %#lx.\n", dwCDBaseValue3);
    printf("dwCDBaseValue2 after: %#lx.\n", dwCDBaseValue4);
}
