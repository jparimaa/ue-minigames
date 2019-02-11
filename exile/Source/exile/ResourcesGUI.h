// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyGameMode.h"
#include "ResourcesGUI.generated.h"

/**
 *
 */
UCLASS()
class EXILE_API UResourcesGUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void InitGameMode();

	/** FText value displayed by this widget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText DisplayText;

	/** Retrieves FText value currently held in DisplayText */
	UFUNCTION(BlueprintPure, Category = "Widgets|Text")
		FText GetDisplayText() const;

	/** Assigns passed FText to DisplayText */
	UFUNCTION(BlueprintCallable, Category = "Widgets|Text")
		void SetDisplayText(const FText& gmt_NewDisplayText);

	UPROPERTY(VisibleAnywhere)
		AMyGameMode* m_gameMode = nullptr;
};
