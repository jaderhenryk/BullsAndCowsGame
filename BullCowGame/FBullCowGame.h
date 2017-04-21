/* a lógica do jogo (sem código de interface de usuário ou interação direta com o usuário). 
O jogo é simplesmente tentar acertar a palavra secreta dentro de um limite de tentativas
*/

#pragma once
#include <string>

// adaptando a sintaxe utilizad na Unreal Engine
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
	FBullCowGame(); // construtor

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
	int32 MyCurrentTry;
	int32 MyGameLevel;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};