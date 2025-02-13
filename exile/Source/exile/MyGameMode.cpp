#include "MyGameMode.h"
#include "ResourcesGUI.h"
#include "Storage.h"
#include "Resident.h"
#include "EngineUtils.h"

#include <vector>
#include <algorithm>

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	changeMenuWidget(m_startingWidgetClass);

	int numResidents = 0;
	for (TActorIterator<AResident> iter(GetWorld()); iter; ++iter)
	{
		++numResidents;
	}
	increaseNumResidents(numResidents);

	for (TActorIterator<ABuildingSpawner> iter(GetWorld()); iter; ++iter)
	{
		m_buildingSpawner = *iter;
	}
	check(m_buildingSpawner != nullptr);

	updateResources();
}

void AMyGameMode::changeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass)
{
	if (m_currentWidget != nullptr)
	{
		m_currentWidget->RemoveFromViewport();
		m_currentWidget = nullptr;
	}
	if (newWidgetClass != nullptr)
	{
		m_currentWidget = CreateWidget<UUserWidget>(GetWorld(), newWidgetClass);
		if (m_currentWidget != nullptr)
		{
			m_currentWidget->AddToViewport();
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
	uint16 totalFoodAmount = 0;
	for (TActorIterator<AStorage> iter(GetWorld()); iter; ++iter)
	{
		totalWoodAmount += iter->getResourceAmount(AStorage::Resource::Wood);
		totalFoodAmount += iter->getResourceAmount(AStorage::Resource::Food);
	}
	m_resourcesGUI->setAmountWood(totalWoodAmount);
	m_resourcesGUI->setAmountFood(totalFoodAmount);
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

	if (m_numResidents == 0)
	{
		changeMenuWidget(m_restartWidgetClass);
	}
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

void AMyGameMode::addNumGatherers(int amount)
{
	updateToWorkers(amount, m_numGatherers);
	checkNumResidentsAndProfessions();
	m_resourcesGUI->setNumGatherers(m_numGatherers);
	updateResidentProfessions();
}

ABuildingSpawner* AMyGameMode::getBuildingSpawner()
{
	return m_buildingSpawner;
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
	check(m_numResidents == (m_numTreeCutters + m_numBuilders + m_numWorkers + m_numGatherers));
}

void AMyGameMode::updateResidentProfessions()
{
	std::vector<AResident*> residents;

	TMap<AResident::Profession, int> numProfessions;
	numProfessions.Add(AResident::Profession::Worker, m_numWorkers);
	numProfessions.Add(AResident::Profession::TreeCutter, m_numTreeCutters);
	numProfessions.Add(AResident::Profession::Builder, m_numBuilders);
	numProfessions.Add(AResident::Profession::Gatherer, m_numGatherers);

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
