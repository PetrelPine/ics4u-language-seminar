/*
* PVZ Cheat
* Language Seminar Assignment
* Written by PetrelPine
* https://github.com/PetrelPine/ics4u-language-seminar
*/

#pragma once

#include <stdio.h>

namespace pvzCheatUtil {
	static HWND hwnd;
	static HANDLE hProcess;

	void hookProcess() {
		// find game process
		hwnd = FindWindow(NULL, L"Plants vs. Zombies");
		if (hwnd == NULL) {
			::MessageBox(hwnd, L"Cannot find PVZ window!", L"Error", MB_OK);
			exit(-1);  // exit program
		}
		//else printf("SUCCESS: Window found.\n");

		// find game process ID
		DWORD dwPID = 0;
		GetWindowThreadProcessId(hwnd, (LPDWORD)&dwPID);
		if (dwPID == 0) {
			::MessageBox(hwnd, L"Cannot find process ID!", L"Error", MB_OK);
			exit(-1);  // exit program
		}
		//else printf("SUCCESS: Process ID found.\n");

		// access game process
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
		if (hProcess == NULL) {
			::MessageBox(hwnd, L"Cannot open process!", L"Error", MB_OK);
			exit(-1);  // exit program
		}
		//else printf("SUCCESS: Process opened.\n");
	}

	DWORD ReadMemory(DWORD placeHolder, ...) {
		if (hProcess == NULL) return -1;

		DWORD lastAddress = 0;
		DWORD offset = 0;
		DWORD lastAddressValue = 0;

		va_list addresses;
		va_start(addresses, placeHolder);

		while ((offset = va_arg(addresses, DWORD)) != -1) {
			lastAddress = lastAddressValue + offset;
			if (0 == ReadProcessMemory(hProcess,
				(LPCVOID)lastAddress,
				&lastAddressValue,
				sizeof(DWORD),
				NULL)) {
				printf("ERROR: ReadMemory failed, last address: %#lx.\n", lastAddress);
				
				::MessageBox(hwnd, L"Read Memory Failed!", L"Error", MB_OK);
				exit(-1);
			}
		}

		va_end(addresses);

		return lastAddressValue;
	}

	void WriteMemory(void* valueToWrite, DWORD valueSize, ...) {
		if (valueToWrite == NULL || valueSize == 0 || hProcess == NULL) return;

		DWORD lastAddress = 0;
		DWORD offset = 0;
		DWORD lastAddressValue = 0;

		va_list addresses;
		va_start(addresses, valueSize);

		while ((offset = va_arg(addresses, DWORD)) != -1) {
			lastAddress = lastAddressValue + offset;
			if (0 == ReadProcessMemory(hProcess,
				(LPCVOID)lastAddress,
				&lastAddressValue,
				sizeof(DWORD),
				NULL)) {
				printf("ERROR: ReadMemory failed, last address: %#lx.\n", lastAddress);
				::MessageBox(hwnd, L"Read Memory Failed!", L"Error", MB_OK);

				exit(-1);
			}
		}
		va_end(addresses);

		if (0 == WriteProcessMemory(
			hProcess,
			(LPVOID)lastAddress,
			valueToWrite,
			valueSize,
			NULL)) {
			printf("ERROR: WriteMemory failed, last address: %#lx.\n", lastAddress);
			::MessageBox(hwnd, L"Write Memory Failed!", L"Error", MB_OK);

			exit(-1);

		}
	}

	DWORD readSunNum() {
		DWORD dwSunBaseAddress = 0x6A9EC0;  // base address
		DWORD dwSunFirstOffset = 0x768;  // first offset address
		DWORD dwSunSecondOffset = 0x5560;  // second offset address

		DWORD dwSunNum = 0;  // store sun number
		dwSunNum = ReadMemory(-1, dwSunBaseAddress, dwSunFirstOffset, dwSunSecondOffset, -1);

		return dwSunNum;
	}

	void changeSunNum(DWORD* dwSunNumNew) {
		DWORD dwSunBaseAddress = 0x6A9EC0;  // base address
		DWORD dwSunFirstOffset = 0x768;  // first offset address
		DWORD dwSunSecondOffset = 0x5560;  // second offset address

		// write new sun number
		WriteMemory(dwSunNumNew, sizeof(dwSunNumNew), dwSunBaseAddress, dwSunFirstOffset, dwSunSecondOffset, -1);
		// print message
		printf("Sun number is changed to %lu.\n", *dwSunNumNew);
	}


	void noCD(boolean choice) {
		DWORD dwCDBaseAddress = 0x487296;
		//BYTE dataNoCDOn[] = {0x90, 0x90};  // 注释后面加空格？注释快捷键？
		BYTE dataNoCDOn[] = { 0x90, 0x90 };
		BYTE dataNoCDOff[] = { 0x7E, 0x14 };

		// test before
		DWORD dwCDBaseValue1 = 0;
		DWORD dwCDBaseValue2 = 0;

		dwCDBaseValue1 = ReadMemory(-1, dwCDBaseAddress, -1);
		dwCDBaseValue2 = ReadMemory(-1, dwCDBaseAddress + sizeof(BYTE), -1);

		printf("dwCDBaseValue1 before: %#lx.\n", dwCDBaseValue1);
		printf("dwCDBaseValue2 before: %#lx.\n", dwCDBaseValue2);

		if (choice) {
			WriteMemory(dataNoCDOn, sizeof(dataNoCDOff), dwCDBaseAddress, -1);
			printf("Plants no CD is ON.\n");
		}
		else {
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
}
