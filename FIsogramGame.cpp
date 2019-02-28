#include "FIsogramGame.h"
#include <map>
#pragma once

//to make syntax Unreal friendly
using int32 = int;
#define TMap std::map

FIsogramGame::FIsogramGame() { Reset(); } //default constructor

int32 FIsogramGame::GetCurrentTry() const{ return MyCurrentTry; }
int32 FIsogramGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FIsogramGame::IsGameWon() const { return bGameIsWon; }

int32 FIsogramGame::GetMaxTries() const {
	TMap<int32, int32> WordLegthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,15}, {7,20} }; //difficulty table
	return WordLegthToMaxTries[MyHiddenWord.length()];
}

void FIsogramGame::Reset() 
{
	const FString HIDDEN_WORD = "recnik"; //this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}





EGuessStatus FIsogramGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght())
	{
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
	

}




//recieves a valid guess incriments turn, and returns counts
FBullCowCount FIsogramGame::SubmitValidGuess(FString Guess)
{
	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); //assuming the same length as guess

	//loop through all letters in the hidden word

	for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++) {	
			//if they match then				
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {				
				if (MHWChar == GChar) {	//if they're in the same place
					BullCowCount.Bulls++;	//incriment bulls
				}
				else {
					BullCowCount.Cows++;	//must be a cow
				}
			}

		}
	}
	if (BullCowCount.Bulls == WordLenght) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FIsogramGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;  //setup our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);
	//loop through all the letters of the word
		
		if (LetterSeen[Letter])//if the letter is in the map
		{
			return false;//we do NOT have an isogram
		} else {   //otherwise
			LetterSeen[Letter] = true;	//add the letter to the map as seen	
		}	
	}
	return true; //for example in cases where /0 is entered
}

bool FIsogramGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
		else return true;
	}
}

