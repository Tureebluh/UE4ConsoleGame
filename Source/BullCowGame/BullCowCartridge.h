// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void IsCorrect(const FString & Input);
	void DisplayCorrectChars(const FString& Guess);
	void SetupGame();
	void SetRandomWord();
	void EndGame();
	void NextWord();
	bool IsIsogram(const FString& CheckWord);
	void WelcomePlayer();
	void PromptUser();

	// Your declarations go below!
	private:
	FString HiddenWord;
	FString ErrorMessage;
	FString CorrectChars;
	int32 TotalLives;
	bool bGameOver;
};
