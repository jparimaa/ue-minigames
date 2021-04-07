#include "TowerTile.h"

ATowerTile::ATowerTile()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	MeshComp->SetupAttachment(RootComponent);
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object) {
		MeshComp->SetStaticMesh(MeshAsset.Object);
		OnClicked.AddDynamic(this, &ATowerTile::OnClick);
	}
}

void ATowerTile::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AtdGameModeBase>(GetWorld()->GetAuthGameMode());
	check(GameMode);
}

void ATowerTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerTile::OnClick(AActor* Actor, FKey	 ButtonPressed)
{
	GameMode->ClickTile(Actor);
}
