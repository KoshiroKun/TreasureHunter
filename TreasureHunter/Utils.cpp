/*
@author Kuroud0
@version 1.00
@date 05/03/2018
*/
#pragma once
#include "Utils.h"
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#define int32 int
#define FString std::string
#define FText std::string

// capture input from user and checks if is a valid number
int32 Utils::CaptureIntFromUser(FText message)
{
	int32 Response = 0;
	FString Input = "";

	do
	{
		std::cout << message;
		std::getline(std::cin, Input);

		// This code converts from string to number safely.
		std::stringstream MyStream(Input);
		if (MyStream >> Response) return Response;
		std::cout << std::endl << "That's not a number :(" << std::endl << std::endl; //FIXME im not happy with this, change it
	} while (true);
	return Response;
}

// clear the console screen without using system functions
void Utils::ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
	return;
}
