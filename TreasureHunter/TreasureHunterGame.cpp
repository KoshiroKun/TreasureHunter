/*
	@author Kuroud0
	@version 1.00
	@date 05/03/2018
*/
#pragma once
#include <stdlib.h>
#include <random>
#include <iostream>
#include "TreasureHunterGame.h"
#include "Utils.h"

TreasureHunterGame::TreasureHunterGame() { Reset(); }
int32 TreasureHunterGame::GetRandomKey() const { return RandomKey; }
int32 TreasureHunterGame::GetMaxTries() const { return MaxTries; }
int32 TreasureHunterGame::GetCurrentTry() const { return CurrentTry; }
bool TreasureHunterGame::IsGameWon() const { return bIsGameWon; }
bool TreasureHunterGame::IsChestLeaved() const { return bLeaveTheChest; }

void TreasureHunterGame::Reset()
{
	MinNumber = 1;
	MaxNumber = 99;
	CurrentTry = 1;
	MaxTries = 5; //FIXME change this value
	bIsGameWon = false;
	bLeaveTheChest = false;
	ListOfCalculatedClues.clear();
	RandomKey = GenerateRandomKey(MinNumber, MaxNumber);
	CreateClues(); // calculate the clues in initialization time
}

void TreasureHunterGame::Menu(int32 Option)
{
	int32 KeyFromUser = 0;
	switch (Option)
	{
	case 1: // Try to open the chest!
		KeyFromUser = TryToOpenChest();
		if (!bIsGameWon)
		{
			// display a clue greather/lower than, but not in the final turn
			if (CurrentTry < MaxTries)
			{
				if (RandomKey > KeyFromUser) std::cout << "The key is greather than " << KeyFromUser;
				else std::cout << "The key is lower than " << KeyFromUser;
			}
			
			std::cout << std::endl << std::endl;
			// increase try number
			CurrentTry++;
		}
		break;
	case 2: // Ask for a clue
		AskForClue();
		break;
	case 3: // Leave the chest
		LeaveTheChest();
		break;
	case 4: // Exit game
		ExitGame();
		break;
	default: // Non valid option
		std::cout << "You must select a valid option between 1-4" << std::endl;
		break;
	}
}

int32 TreasureHunterGame::TryToOpenChest()
{
	FText message = "> Enter a number from " + std::to_string(MinNumber) + " to " + std::to_string(MaxNumber) + ": ";
	int32 KeyFromUser = Utils::CaptureIntFromUser(message);
	bIsGameWon = (KeyFromUser == RandomKey) ? true : false;
	return KeyFromUser;
}

void TreasureHunterGame::AskForClue()
{
	// if the list if empty, display a warning without spend a try
	if (ListOfCalculatedClues.empty())
	{
		std::cout << "No more clues are available :(" << std::endl;
	}
	else
	{
		int32 RandomClue = GenerateRandomKey(0, ListOfCalculatedClues.size());
		auto iterator = std::next(ListOfCalculatedClues.begin(), RandomClue);
		std::cout << *iterator << std::endl << std::endl;

		// remove the clue already presented
		ListOfCalculatedClues.remove(*iterator);

		// spend a try
		CurrentTry++;
	}

	//std::cout << "DEBUG - The first digit is: " + std::to_string(RandomKey / 10) << std::endl;
	//std::cout << "DEBUG - The second digit is: " + std::to_string(RandomKey % 10) << std::endl;
	return;
}

void TreasureHunterGame::LeaveTheChest()
{
	std::cout << "> Are you sure you want to leave the chest (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response.size() > 0 && ('Y' == Response[0] || 'y' == Response[0]))
	{
		CurrentTry = MaxTries + 1; // with this, we will exit from the current game
		bLeaveTheChest = true;
	}
	return;
}

void TreasureHunterGame::ExitGame()
{
	std::cout << std::endl << "See you soon!" << std::endl;
	std::exit(EXIT_SUCCESS);
	return;
}

// Generates a random number key from MIN_NUMBER to MAX_NUMBER both included
int32 TreasureHunterGame::GenerateRandomKey(int32 MinNumber, int32 MaxNumber)
{
	// TODO display an error if min number is greather than max number
	if (MinNumber > MaxNumber) return -1;

	// Provided by C++11
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(MinNumber, MaxNumber);

	return dist(mt);
}


// Check if the given number is pair or odd
int32 TreasureHunterGame::IsNumberOdd(int32 Number) { return Number % 2; }

// Sum both digits of the given number
int32 TreasureHunterGame::SumDigitsKey(int32 Number)
{
	int32 firstDigit = Number / 10;
	int32 secondDigit = Number % 10;
	return firstDigit + secondDigit;
}

void TreasureHunterGame::CreateClues()
{
	int32 numberBelow = GenerateRandomKey(MinNumber, RandomKey);
	int32 numberAbove = GenerateRandomKey(RandomKey, MaxNumber);
	FString firstDigitValue = IsNumberOdd(RandomKey / 10) ? "odd" : "pair";
	FString secondDigitValue = IsNumberOdd(RandomKey % 10) ? "odd" : "pair";

	ListOfCalculatedClues.push_back("The first digit is " + firstDigitValue);
	ListOfCalculatedClues.push_back("The second digit is " + secondDigitValue);
	ListOfCalculatedClues.push_back("The sum of the digits is " + std::to_string(SumDigitsKey(RandomKey)));
	ListOfCalculatedClues.push_back("The number is between " + std::to_string(numberBelow) + " and " + std::to_string(numberAbove));
	return;
}
