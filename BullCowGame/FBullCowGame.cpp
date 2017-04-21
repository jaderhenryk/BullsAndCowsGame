#pragma once

#include "FBullCowGame.h"
#include <map>
#include <time.h>

// to make syntax Unreal friendly
#define TMap std::map
using FString = FString;
using int32 = int;

// default constructor
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
	MyHiddenWord = "planet"; // this MUST be an isogram
	MyCurrentTry = 1;
	MyGameLevel = 2;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuesValidity(FString Guess) const {
	if (!IsIsogram(Guess)) { // if the guess isn't an ISOGRAM	
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) { // if the guess isn't all lowercase
		return EGuessStatus::Not_Lowercase; 
	} else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong 
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

// choose randomly a word from one of arrays according to level selected by player
void FBullCowGame::SetHiddenWordByLevelDifficulty()
{
	FString EasyDifficultyWords[10] = { "ant", "sky", "pie", "bat", "owl", "bird", "goal", "dice", "fire", "tomb" }; // easy words array
	FString NormalDifficultyWords[10] = { "planet", "black", "final", "light", "horse", "bridge", "monkey", "gremio", "dragon", "square" }; // normal words array
	FString HardDifficultyWords[5] = { "pikachu", "soldier", "special", "kremlin", "banquet" }; // hard words array

	int32 MySelectedLevel = GetMyGameLevel();
	srand((unsigned) time(NULL)); // set the seed based in time to generate always a different seed to prevent generate the same random number

	// check the level and get a word from array position of generated random number
	if (MySelectedLevel == 1) {
		this->MyHiddenWord = EasyDifficultyWords[rand() % 10];
	} else if (MySelectedLevel == 2) {
		this->MyHiddenWord = NormalDifficultyWords[rand() % 10];
	} else if (MySelectedLevel == 3) {
		this->MyHiddenWord = HardDifficultyWords[rand() % 5];
	}
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) { 
				// if they're in the same place
				if (MHWChar == GChar) { 
					// incriment bulls
					BullCowCount.Bulls++; 
				} else {
					// must be a cow
					BullCowCount.Cows++; 
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

// Set the game level based in player choice
void FBullCowGame::SetMyGameLevel(int32 MyGameLevel) {
	this->MyGameLevel = MyGameLevel;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;
	// loop through all letters of the word
	for (auto Letter : Word) {
		Letter = tolower(Letter); // handle mixed case
		// if the letter is in the map
		if (LetterSeen[Letter]) {
			return false; // we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true; // add the letter to the map
		}

	}
  	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) { // if not a lowercase letter
			return false;
		}
	}
	return true;
}
