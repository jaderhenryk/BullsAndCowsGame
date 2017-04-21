/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;
#define TMap std::map

// instantiate a new game, which we re-use across plays
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void AskGameDifficulty();

FBullCowGame BCGame; // instanciando um novo jogo

TMap<int32, FString> GameDifficultyText{ { 1, "Easy" },{ 2, "Normal" },{ 3, "Hard" } }; // mapa com as definições de levels

																						// the entry point for our application
int main() {

	do {
		system("cls");
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

void PrintIntro() {

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {        (___)" << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame() {

	BCGame.Reset();

	AskGameDifficulty();

	std::cin.ignore();
	std::cout << "Game Difficulty: " << GameDifficultyText[BCGame.GetMyGameLevel()] << "\n\n";

	std::cout << "Can you guess the letter " << BCGame.GetHiddenWordLength();
	std::cout << " isogram I'm thinking of? " << "**" << BCGame.GetMyHiddenWord() << "**\n";

	int32 MaxTries = BCGame.GetMaxTries();
	
	std::cout << "Max Tries: " << MaxTries << std::endl;

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.isGameWon() && BCGame.GetCurrentTry() < MaxTries) {
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << " . Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuesValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only words in lowercase.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeat letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');

}

void PrintGameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << "WELL DONE YOU HAVE WON!\n";
	} else {
		std::cout << "Better luck next time!\n";
	}
}

void AskGameDifficulty() {
	int32 Choice = 0;
	
	do {
		std::cout << "Select the difficulty\n";
		std::cout << "1 - Easy\n";
		std::cout << "2 - Normal\n";
		std::cout << "3 - Hard\n\n";
		std::cout << "Option: "; 
		std::cin >> Choice;

	} while (Choice < 1 || Choice > 3);
	
	BCGame.SetMyGameLevel(Choice);
	BCGame.SetHiddenWordByLevelDifficulty();
}
