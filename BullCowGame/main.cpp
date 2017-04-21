/* Este é um aplicativo de console, que faz uso da classe BullCow
Este arquivo atua como a view no padrão MVC, e é responsável por toda a
interação com o usuário. Para ver a lógica do jogo veja a classe FBullCowGame.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>

// adaptando a sintaxe utilizad na Unreal Engine
using FText = std::string;
using int32 = int;
#define TMap std::map

// protótipos das funções utilizadas fora da classe do jogo
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void AskGameDifficulty();

FBullCowGame BCGame; // instanciando um novo jogo

TMap<int32, FString> GameDifficultyText{ { 1, "Easy" },{ 2, "Normal" },{ 3, "Hard" } }; // mapa com as definições de levels

// ponto de inicial da aplicação
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

void PlayGame() {

	BCGame.Reset();

	AskGameDifficulty();

	std::cin.ignore();
	std::cout << "Game Difficulty: " << GameDifficultyText[BCGame.GetMyGameLevel()] << "\n\n";

	std::cout << "Can you guess the letter " << BCGame.GetHiddenWordLength();
	std::cout << " isogram I'm thinking of? " << "**" << BCGame.GetMyHiddenWord() << "**\n";

	int32 MaxTries = BCGame.GetMaxTries();
	
	std::cout << "Max Tries: " << MaxTries << std::endl;

	// continua perguntando os palpites do jogador
	// até que ele acerte a palavra ou esgote o numero de tentativas
	while (!BCGame.isGameWon() && BCGame.GetCurrentTry() < MaxTries) {
		FText Guess = GetValidGuess(); 

		// verifica e valida o palpite do usuário e retorna a contagem de Bulls e Cows
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

	}

	PrintGameSummary();
	return;
}

FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// pega o palpite do usuário
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << " . Enter your guess: ";
		std::getline(std::cin, Guess);

		// checa se o palpite é válido
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
			break;
		}
	} while (Status != EGuessStatus::OK); // continua perguntando ao usuário o palpite enquanto ele for inválido
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
