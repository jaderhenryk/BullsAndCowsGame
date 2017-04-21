/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetMyGameLevel();
	FString GetMyHiddenWord() const;
	bool isGameWon() const;
	EGuessStatus CheckGuesValidity(FString) const; 
	void SetHiddenWordByLevelDifficulty();

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

	void SetMyGameLevel(int32);

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyGameLevel;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};