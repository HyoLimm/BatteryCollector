// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"
// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	WhereToSpawn=CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
	

	//아이템 생성 최소/최대 딜레이 범위
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;
}




// Called when the game starts or when spawned
//void ASpawnVolume::BeginPlay()
//{
//	Super::BeginPlay();
//}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);

}


void ASpawnVolume::SpawnPickup()
{
	if (WhatToSpawn != NULL) {
		UWorld * const World = GetWorld();
		if (World) {
	
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;


			//만드는위치 랜덤으로 고름
			FVector SpawnLocation = GetRandomPointInVolume();


			//생성한 아이템 랜덤한 로테이션값 넣어줌
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;


			//아이템 생성
			APickup * const SpawnedPickup= World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);



			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh); //랜덤 값 출력
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
		}



	}

}


void ASpawnVolume::SetSpawingActive(bool bShouldSpawn)
{
	
	if (bShouldSpawn) {
		//스폰되게

		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh); //랜덤 값 출력
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	}	
	else {
		//안되게
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}

}