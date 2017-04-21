#pragma once

#include "FBullCowGame.h"
#include <map>
#include <time.h>

// adaptando a sintaxe utilizad na Unreal Engine
#define TMap std::map
using FString = FString;
using int32 = int;

// contrutor padrão
FBullCowGame::FBullCowGame() { 
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetMyGameLevel() { return MyGameLevel; }
FString FBullCowGame::GetMyHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::isGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,6}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset() {
	MyHiddenWord = "planet";
	MyCurrentTry = 1;
	MyGameLevel = 2;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuesValidity(FString Guess) const {
	if (!IsIsogram(Guess)) { // verifica se o palpite não é um ISOGRAMA	
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) { // verifica se todas as letras são minusculas
		return EGuessStatus::Not_Lowercase; 
	} else if (Guess.length() != GetHiddenWordLength()) { // verifica o tamanho do palpite 
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

// escolhe aleatóricamente uma palavra de acordo com o level seleciondo
void FBullCowGame::SetHiddenWordByLevelDifficulty()
{
	FString EasyDifficultyWords[10] = { "ant", "sky", "pie", "bat", "owl", "bird", "goal", "dice", "fire", "tomb" };
	FString NormalDifficultyWords[10] = { "planet", "black", "final", "light", "horse", "bridge", "monkey", "gremio", "dragon", "square" };
	FString HardDifficultyWords[5] = { "pikachu", "soldier", "special", "kremlin", "banquet" };

	int32 MySelectedLevel = GetMyGameLevel();
	srand(time(NULL));

	if (MySelectedLevel == 1) {
		this->MyHiddenWord = EasyDifficultyWords[rand() % 10];
	} else if (MySelectedLevel == 2) {
		this->MyHiddenWord = NormalDifficultyWords[rand() % 10];
	} else if (MySelectedLevel == 3) {
		this->MyHiddenWord = HardDifficultyWords[rand() % 5];
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// intera sobre as letras da palavra secreta
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compara as letras da palavra secreta com o palpite do usuário
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) { // se a letra confere
				if (MHWChar == GChar) { // se a letra está na posição correta
					BullCowCount.Bulls++; // incrementa Bulls
				} else {
					BullCowCount.Cows++; // incrementa Cows
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

void FBullCowGame::SetMyGameLevel(int32 MyGameLevel) {
	this->MyGameLevel = MyGameLevel;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else {
			LetterSeen[Letter] = true;
		}

	}
  	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
