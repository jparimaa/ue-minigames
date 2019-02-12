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
