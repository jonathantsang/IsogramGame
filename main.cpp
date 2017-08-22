// Project.cpp : Defines the entry point for the console application.
//

/* THis is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class. 
*/

#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game


int32 main()
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

void PrintIntro() {
	// introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// Submit valid guess to the game
		BullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}

	// TODO summarise game
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		
		getline(std::cin, Guess);
		// Check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get valid input
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with thr same hidden word (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!\n" << std::endl;
	}
}