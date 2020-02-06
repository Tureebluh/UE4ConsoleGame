// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	SetupGame();
}

void UBullCowCartridge::SetupGame()
{
	bGameOver = false;
	TotalLives = 3;
	SetRandomWord();
	WelcomePlayer();
}

void UBullCowCartridge::WelcomePlayer()
{
	ClearScreen();
	PrintLine(TEXT("Welcome to Bull Cows!"));
	PrintLine(TEXT("\nPress TAB to enter the terminal."));
	PrintLine(TEXT("\nThen press Enter to continue..."));
}

void UBullCowCartridge::PromptUser()
{
	ClearScreen();
	PrintLine(TEXT("%s"), *ErrorMessage);
	ErrorMessage = "";//Clear error message after displaying.

	PrintLine(TEXT("Guess the correct %i letter isogram."), HiddenWord.Len());

	PrintLine(TEXT("\nCorrect attempts: " + CorrectChars));

	PrintLine(TEXT("\nLives remaining: %i"), TotalLives);
}

void UBullCowCartridge::EndGame()
{
	ClearScreen();
	PrintLine(TEXT("Zero lives remaining.\nYour hidden word was %s"), *HiddenWord);
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to continue..."));
}

void UBullCowCartridge::NextWord()
{
	TotalLives = 3;
	SetRandomWord();
	ClearScreen();
	PrintLine(TEXT("Congratulations! You completed the level."));
	PrintLine(TEXT("\nPress enter to continue..."));
}

void UBullCowCartridge::SetRandomWord()
{
	CorrectChars = "";
	HiddenWord = Words[FMath::RandRange(0, Words.Num() - 1)];

	bool Invalid = true;
	while (Invalid)
	{
		if (IsIsogram(HiddenWord)) 
		{
			Invalid = false;
		}
		else
		{
			HiddenWord = Words[FMath::RandRange(0, Words.Num() - 1)];
		}
	}

	for (int i = 0; i < HiddenWord.Len(); i++) 
	{
		CorrectChars += "_";
	}
}

bool UBullCowCartridge::IsIsogram(const FString& CheckWord)
{
	for (int i = 0; i < CheckWord.Len(); i++)
	{
		for (int k = 0; k < CheckWord.Len(); k++)
		{
			if (CheckWord[i] == CheckWord[k] && (i != k))
			{
				return false;
			}
		}
	}
	return true;
}

void UBullCowCartridge::OnInput(const FString& Input)
{
	if(bGameOver)
	{
		SetupGame();
	}
	else
	{
		IsCorrect(Input);
	}
}

void UBullCowCartridge::IsCorrect(const FString& Input)
{
	if ((Input != ""))
	{
		if (Input.Len() == HiddenWord.Len())
		{
			if (IsIsogram(Input))
			{
				if (Input == HiddenWord)
				{
					NextWord();
				}
				else
				{
					if (TotalLives > 0)
					{
						DisplayCorrectChars(Input);
						TotalLives--;
						PromptUser();
					}
					else
					{
						EndGame();
					}
				}
			}
			else
			{
				ErrorMessage = "*No repeating characters*\n";
				PromptUser();
			}
		}
		else
		{
			ErrorMessage = "*Invalid word length*\n";
			PromptUser();
		}
	}
	else
	{
		PromptUser();
	}
}

void UBullCowCartridge::DisplayCorrectChars(const FString& Guess) 
{
	for (int i = 0; i < HiddenWord.Len(); i++) 
	{
		for (int j = 0; j < Guess.Len(); j++)
		{
			if(HiddenWord[i] == Guess[j])
			{
				CorrectChars[i] = Guess[j];
				break;
			}
		}
	}
}



