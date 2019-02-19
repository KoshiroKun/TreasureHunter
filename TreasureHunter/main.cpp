/*
	Welcome to Treasure Hunter!
	Try to open the treasure chests with a random generated key

	@author Kuroud0
	@version 1.00
	@date 05/03/2018
*/
#pragma once
#include <iostream>
#include <string>
#include "TreasureHunterGame.h"
#include "Utils.h"
#define FText std::string

void PrintIntro();
void PlayGame();
FText PrintMenu();
void PrintGameSummary();
bool AskToPlayAgain();

TreasureHunterGame THGame; // Game initialization

const FText WIN_MESSAGE = "";
const FText LOOSE_MESSAGE = "";

int main()
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	std::cout << std::endl << "See you soon!" << std::endl;
	return 0;
}

// Introduction of the game, add here rules or anything you think is nice to explain to the user
void PrintIntro()
{
	std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
	std::cout << "//                                        Welcome to Treasure Hunter!                                     //" << std::endl;
	std::cout << "//--------------------------------------------------------------------------------------------------------//" << std::endl;
	std::cout << "// - You will have a number of attempts to guess the random generated key (0-99) of the treasure chest... //" << std::endl;
	std::cout << "// - If you wish you can spend tries in order to get clues from the system                                //" << std::endl;
	std::cout << "//--------------------------------------------------------------------------------------------------------//" << std::endl;
	std::cout << "//                                                                                Good Luck and Have Fun! //" << std::endl;
	std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	//std::cout << "DEBUG - Random number generated: " << THGame.GetRandomKey() << std::endl;
	int32 UserOption = 0;
	std::cout << " == You found a treasure chest! == " << std::endl << std::endl;

	while (!THGame.IsGameWon() && THGame.GetCurrentTry() <= THGame.GetMaxTries())
	{
		UserOption = Utils::CaptureIntFromUser(PrintMenu()); // prints the menu and retrieves the user option
		//std::cout << "DEBUG - Option " << UserOption << " entered" << std::endl;
		THGame.Menu(UserOption); // performs the action selected by the user
	}

	if (!THGame.IsChestLeaved()) PrintGameSummary();
	THGame.Reset();
	return;
}

FText PrintMenu()
{
	FText menu = "";
	menu = "==============================\n";
	menu += "|          Try: " + std::to_string(THGame.GetCurrentTry()) + "/" + std::to_string(THGame.GetMaxTries()) + "          |\n";
	menu += "==============================\n";
	menu += "| 1.- Try to open the chest! |\n";
	menu += "| 2.- Ask for a clue         |\n";
	menu += "| 3.- Leave the chest        |\n";
	menu += "| 4.- Exit game              |\n";
	menu += "==============================\n";
	menu += "> What do you want to do?  ";
	return menu;
}

void PrintGameSummary()
{
	if (THGame.IsGameWon()) std::cout << "CONGRATULATIONS! - You open the chest!" << std::endl;
	else std::cout << "Sorry :( - You do not open the chest. The number was: " << THGame.GetRandomKey() << std::endl;
	return;
}

bool AskToPlayAgain()
{
	std::cout << "> Do you want to play Treasure Hunter again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	bool bPlayAgain = (Response.size() > 0 && ('Y' == Response[0] || 'y' == Response[0]));
	if (bPlayAgain) Utils::ClearScreen();
	return (bPlayAgain);
}
