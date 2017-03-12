/* This is the console executable that mkes use of the BullCow Class.
This acts as the view in a MVC pattern and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// prototyping - prototypes as outside a class.
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();


FBullCowGame BCGame; //instantiate a new game, which we re-use across plays.

// The entry point for our game.
int main()
{

	do
	{
		PrintIntro();
		PlayGame();
	}
	while(PlayAgain());
	
	return 0; //exit the application
}

// Loop for the number of turns asking for guesses.


// Introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Cows and Bulls, dude! It's a fun word game.\n\n";
		

std::cout << "	                   o==+--       \n";
std::cout << "                            |  |\\   \n";
std::cout << "                            |  | \\        ____________________   \n";
std::cout << "                            |   \\ \\      |                  |  \n";
std::cout << "                            |    \\ \\     |  +------------+  |  \n";
std::cout << "                            |     \\ \\    |  |     (__)   |  |  \n";
std::cout << "                            |      \\ \\   |  |     (oo)   |  |  \n";
std::cout << "                            |       \\ \\  |  | o\\  .\\/.   |  |  \n";
std::cout << "                            |        \\ \\ |  | | \\/    \\  |  |  \n";
std::cout << "                          /---\\       \\  |  +------------+  |  \n";
std::cout << "    SHIT....             /     \\       \\ |                  |  \n";
std::cout << "                         |     |         |       COW        |  \n";
std::cout << "          }   {          \\     /         |                  |  \n";
std::cout << "          (o o)           \\VVV/          |                  |  \n";
std::cout << "   /-------\\ /                           |                  |  \n";
std::cout << "  / | BULL |O                         --------------------------  \n";
std::cout << " *  |-,--- |                         (                          )  \n";
std::cout << "    ^      ^                          --------------------------  \n";

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

/**************************************************************************|
TODO: MAKE USER CHOOSE WORD LENGTH - ADD RANDOM WORDS FOR EACH WORD LENGTH |
|**************************************************************************/

bool PlayAgain()
{
	std::cout << "\nDo you want to play again with the same hidden word? (y/n) \n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// Main game loop - plays a single game to completion.
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	//Loop asking for guesses while the game is NOT won
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 
		
		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
				
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	PrintGameSummary();
	return;
}

//loop continually to get a valid guess.
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

		//get a guess from the player	
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try # " << CurrentTry << " / " << BCGame.GetMaxTries() << " - Enter your guess: ";

		std::getline(std::cin, Guess);

		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Your word is not lowercase. \n\n";
			break;
		default:
			//assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get valid user input, or no errors.
	
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nCONGRATULATIONS! - YOU WIN!! \n";
	}
	else if (BCGame.GetCurrentTry() >= BCGame.GetMaxTries())
	{
		std::cout << "\nBetter luck next time! \n";
	}
}

