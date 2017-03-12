/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

// to make syntax unreal friendly
using FString = std::string;
using int32 = int;

// **PERSONAL NOTES: A class is like a factory. It spits out cars, and they all come out the same. Their properties can change.


struct FBullCowCount           //Same as a class, but all members are public by default.
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	//Not_Alphabetical_Word,
	//No_Word_Entered,
	Wrong_Length,
	Not_Lowercase,
};


class FBullCowGame {
public:
	
	FBullCowGame(); //constructor


	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	
	// counts bulls & cows and increments the try number, assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);


// Please try anad ignore this and focus on the interface above.
private:
	//see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};