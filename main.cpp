/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FIsogramGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FIsogramGame.h"

//to make szintax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro(); 
void PlayGame(); 
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FIsogramGame IGame; //instantiate a new game which we use across play

//entry point for game
int main()
{
	std::cout << IGame.GetCurrentTry();

	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain); 
	return 0; //exit the app
}


void PrintIntro() 
{
	std::cout << "\n\nDobrodosli u najbolju igru na svetu\n";
	std::cout << "da li mozes da pogodis " << IGame.GetHiddenWordLenght();
	std::cout << " slova isograma na koji mislim ?\n";
	std::cout << std::endl;
}

//play a single game to completion
void PlayGame()
{
	IGame.Reset();
	int32 MaxTries = IGame.GetMaxTries();
	
	//loop asking for guesses while the game 
	//is NOT won and there are still tries remaining
	while(!IGame.IsGameWon() && IGame.GetCurrentTry() <= MaxTries)	{
		FText Guess = GetValidGuess(); 
				
		//submit valid guess to the game, and recieve the counts
		FBullCowCount BullCowCount = IGame.SubmitValidGuess(Guess);
				
		std::cout << "Na dobrom mestu = " << BullCowCount.Bulls;
		std::cout << ". Pogodjena = " << BullCowCount.Cows << "\n\n"; 
	}
	
	PrintGameSummary();
	return;
}
// loop continualy until the users gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from player
		int32 CurrentTry = IGame.GetCurrentTry();

		std::cout << "Pokusaj br. " << CurrentTry << " od " << IGame.GetMaxTries();
		std::cout <<". Ukucaj svoju rec : ";
			std::getline(std::cin, Guess);

			//check guess validity
			Status = IGame.CheckGuessValidity(Guess);
			switch (Status)
			{
			case EGuessStatus::Wrong_Length:
				std::cout << "molim te ukucaj rec sa  " << IGame.GetHiddenWordLenght() << " slova.\n\n";
				break;
			case EGuessStatus::Not_Isogram:
					std::cout << "Molim te ukucaj rec kod koje se ne ponavljaju slova.\n\n";
					break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "koristi samo mala slova.\n\n";
				break;
			default:
				//assume the guess is valid
				break;
			}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Da li zelis da igras ponovo sa istom skrivenom recju? (d/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'd') || (Response[0] == 'D');
}
void PrintGameSummary()
{
	if (IGame.IsGameWon())
	{
		std::cout << "Bravo! Pobedio si!\n";
	}
	else
	{
		std::cout << "Izgubio si, vise srece sledeci put.\n";
	}
}



