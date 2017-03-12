#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax unreal friendly
#define TMap std::map 
using int32 = int;



// Default constructor
FBullCowGame::FBullCowGame(){ Reset(); }

//Getters to go get variable data. Put them all on one line, kind of an industry standard.

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{

	const FString HIDDEN_WORD = "planet"; // This MUST be an ISOGRAM.
	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram, 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) 
	{
		return EGuessStatus::Not_Lowercase; // if the guess isn't all lowercase, 
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		
		return EGuessStatus::Wrong_Length; // if word is wrong length
	}
	else
	{
		return EGuessStatus::OK;
	}
	
		
	// if the guess length is wrong
		// return an error
	// otherwise
		// return OK
}



// receives a VALID guess, increments turn, and re turns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();   //assuming same length as guess
	
	//loop through all letters in the hidden word.
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// Compare letters against the guess.
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)		// if they're in the same places
				{
					BullCowCount.Bulls++; //increment bulls 
				}
				else 
				{
					BullCowCount.Cows++;    // increment cows				
				} 
			}
		}
	}
	
	if (BullCowCount.Bulls == WordLength)
	{		
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms.
	if (Word.length() <= 1) { return true; }

	// set up our map
	TMap <char, bool> LetterSeen;
	for (auto Letter : Word)            //for all letters of the word
	{
		Letter = tolower(Letter);	    // handle mixed case
		if (LetterSeen[Letter]) { return false; } // we do NOT have an isogram at this stage
		else { LetterSeen[Letter] = true; }
		
												  
		// Check if the user's guess is an isogram
		// Loop through all the letters of the word.
			// if the letter is in the map
				// otherwise
				// add the letter to the map as seen. 
	}
	
	
	return true; // for example in cases wehre /0 is entered.
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))      // if not a lower case letter
		{
			return false;
		}
	}
	return true;
}


