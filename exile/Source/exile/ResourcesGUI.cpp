// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourcesGUI.h"

void UResourcesGUI::InitGameMode()
{
	m_gameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
	m_gameMode->setResourcesGUI(this);
}

FText UResourcesGUI::GetDisplayText() const {
	return DisplayText;

}

/** Assigns passed FText to DisplayText */
void UResourcesGUI::SetDisplayText(const FText& NewDisplayText) {
	DisplayText = NewDisplayText;
}
