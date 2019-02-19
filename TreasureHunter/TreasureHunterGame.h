/*
	Game logic

	@author Kuroud0
	@version 1.00
	@date 05/03/2018
*/
#pragma once
#include <string>
#include <list>
#define int32 int
#define FString std::string

class TreasureHunterGame
{
public:
	TreasureHunterGame(); // constructor

	void Reset();
	void Menu(int32);
	int32 TryToOpenChest();
	void AskForClue();
	void LeaveTheChest();
	void ExitGame();

	int32 GetRandomKey() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	bool IsChestLeaved() const;

private:
	// Minimum number
	int32 MinNumber;
	// Maximum number
	int32 MaxNumber;
	// The number key to open the chest, generated randomly
	int32 RandomKey;
	// Max tries in the current game
	int32 MaxTries; // TODO think why increase or decrease this number, maybe a fix value?
	// Current try of the game
	int32 CurrentTry;
	bool bIsGameWon;
	// if the chest is leaved we don't display summary messages
	bool bLeaveTheChest;
	// clues for the user when decide spend a try
	std::list<FString> ListOfCalculatedClues;

	// Generates a random number key from MIN_NUMBER to MAX_NUMBER both included
	int32 GenerateRandomKey(int32 MIN_NUMBER, int32 MAX_NUMBER);
	// Check if the given number is pair or odd
	int32 IsNumberOdd(int32);
	// Sum both digits of the given number
	int32 SumDigitsKey(int32);
	// create the clues and calculate their values
	void CreateClues();
};