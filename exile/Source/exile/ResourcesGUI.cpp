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

void UResourcesGUI::setNumTreeCutters(uint16 numTreeCutters)
{
	m_numTreeCutters = FString::FromInt(numTreeCutters);
}

void UResourcesGUI::setNumBuilders(uint16 numBuilders)
{
	m_numBuilders = FString::FromInt(numBuilders);
}

void UResourcesGUI::setNumGatherers(uint16 numBuilders)
{
	m_numGatherers = FString::FromInt(numBuilders);
}

void UResourcesGUI::setNumWorkers(uint16 numWorkers)
{
	m_numWorkers = FString::FromInt(numWorkers);
}
