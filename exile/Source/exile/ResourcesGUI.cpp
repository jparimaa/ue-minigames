#include "ResourcesGUI.h"

void UResourcesGUI::initGameMode()
{
	m_gameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
	m_gameMode->setResourcesGUI(this);
}

void UResourcesGUI::setAmountWood(uint16 amountWood)
{
	m_amountWood = FString::FromInt(amountWood);
}

void UResourcesGUI::setNumResidents(uint16 numResidents)
{
	m_numResidents = FString::FromInt(numResidents);
}

void UResourcesGUI::setNumWoodCutters(uint16 numWoodCutters)
{
	m_numWoodCutters = FString::FromInt(numWoodCutters);
}

void UResourcesGUI::setNumBuilders(uint16 numBuilders)
{
	m_numBuilders = FString::FromInt(numBuilders);
}

void UResourcesGUI::setNumWorkers(uint16 numWorkers)
{
	m_numWorkers = FString::FromInt(numWorkers);
}
