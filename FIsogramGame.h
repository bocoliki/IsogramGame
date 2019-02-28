/* The game logic (no view code or direct user interaction)
The game is a simple word guess game*/

#pragma once
#include <string>

//to make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};



class FIsogramGame {
public:
	FIsogramGame(); //constructor
	

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const; 
	int32 GetHiddenWordLenght() const;
	
	
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); 	
	FBullCowCount SubmitValidGuess(FString);


private:
	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};