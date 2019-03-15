#include "MyGameMode.h"
#include "ResourcesGUI.h"
#include "Barn.h"
#include "Resident.h"
#include "EngineUtils.h"

#include <vector>
#include <algorithm>

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

	int numResidents = 0;
	for (TActorIterator<AResident> iter(GetWorld()); iter; ++iter)
	{
		++numResidents;
	}
	increaseNumResidents(numResidents);
}

void AMyGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	UE_LOG(LogTemp, Log, TEXT("AMyGameMode::ChangeMenuWidget"));
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AMyGameMode::setResourcesGUI(UResourcesGUI* resourcesGUI)
{
	m_resourcesGUI = resourcesGUI;
}

void AMyGameMode::updateResources()
{
	uint16 totalWoodAmount = 0;
	for (TActorIterator<ABarn> iter(GetWorld()); iter; ++iter)
	{
		totalWoodAmount += iter->getWoodAmount();
	}
	m_resourcesGUI->setAmountWood(totalWoodAmount);
}

void AMyGameMode::increaseNumResidents(int amount)
{
	m_numResidents += amount;
	addNumWorkers(amount);
	checkNumResidentsAndProfessions();
	m_resourcesGUI->setNumResidents(m_numResidents);
}

void AMyGameMode::decreaseNumResidents(int amount)
{
	m_numResidents -= amount;
	int amountLeft = decreaseResidentsFromProfession(amount, m_numWorkers);
	amountLeft = decreaseResidentsFromProfession(amountLeft, m_numTreeCutters);
	amountLeft = decreaseResidentsFromProfession(amountLeft, m_numBuilders);
	checkNumResidentsAndProfessions();

	m_resourcesGUI->setNumResidents(m_numResidents);
	m_resourcesGUI->setNumTreeCutters(m_numTreeCutters);
	m_resourcesGUI->setNumBuilders(m_numBuilders);
	m_resourcesGUI->setNumWorkers(m_numWorkers);
	updateResidentProfessions();
}

void AMyGameMode::addNumTreeCutters(int amount)
{
	updateToWorkers(amount, m_numTreeCutters);
	checkNumResidentsAndProfessions();
	m_resourcesGUI->setNumTreeCutters(m_numTreeCutters);
	updateResidentProfessions();
}

void AMyGameMode::addNumBuilders(int amount)
{
	updateToWorkers(amount, m_numBuilders);
	checkNumResidentsAndProfessions();
	m_resourcesGUI->setNumBuilders(m_numBuilders);
	updateResidentProfessions();
}

void AMyGameMode::addNumWorkers(int amount)
{
	m_numWorkers += amount;
	m_resourcesGUI->setNumWorkers(m_numWorkers);
}

void AMyGameMode::updateToWorkers(int amount, int& profession)
{
	if (amount < 0 && (amount + profession < 0))
	{
		return;
	}
	if (amount > 0 && (m_numWorkers - amount < 0))
	{
		return;
	}
	addNumWorkers(-amount);
	profession += amount;
}

int AMyGameMode::decreaseResidentsFromProfession(int amount, int& profession)
{
	if (amount == 0)
	{
		return 0;
	}
	if (profession >= amount)
	{
		profession -= amount;
		return 0;
	}

	int newAmount = amount - profession;
	profession = 0;
	return newAmount;
}

void AMyGameMode::checkNumResidentsAndProfessions()
{
	check(m_numResidents == (m_numTreeCutters + m_numBuilders + m_numWorkers));
}

void AMyGameMode::updateResidentProfessions()
{
	std::vector<AResident*> residents;

	TMap<AResident::Profession, int> numProfessions;
	numProfessions.Add(AResident::Profession::Worker, m_numWorkers);
	numProfessions.Add(AResident::Profession::TreeCutter, m_numTreeCutters);
	numProfessions.Add(AResident::Profession::Builder, m_numBuilders);

	for (TActorIterator<AResident> iter(GetWorld()); iter; ++iter)
	{
		residents.push_back(*iter);
	}

	auto pred = [&](const AResident* resident)
	{
		AResident::Profession profession = resident->getProfession();
		int& n = numProfessions[profession];
		if (n > 0)
		{
			--n;
			return true;
		}
		return false;
	};

	residents.erase(std::remove_if(residents.begin(), residents.end(), pred), residents.end());

	int index = 0;
	for (auto& kv : numProfessions)
	{
		for (int i = 0; i < kv.Value; ++i)
		{
			check(residents[index] != nullptr);
			residents[index++]->setProfession(kv.Key);
		}
	}
}
