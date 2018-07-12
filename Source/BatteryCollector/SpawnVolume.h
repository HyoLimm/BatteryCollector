// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Engine/World.h"
#include "Components/BoxComponent.h"
#include "Public/TimerManager.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const {
		return WhereToSpawn;
	}

	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

	/*스폰의 작동을 조절하는 함수*/
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void SetSpawingActive(bool bShouldSpawn);
protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Spawning")
		TSubclassOf<class APickup> WhatToSpawn;


	FTimerHandle SpawnTimer;
	//생성시 최소 지연시간
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawning")
		float SpawnDelayRangeLow;
	
	//생성시 최대 지연 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnDelayRangeHigh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Spawning",meta=(AllowPrivateAccess="true"))
		class UBoxComponent* WhereToSpawn;

	//새 아이템 생성
	void SpawnPickup();

	/*현재 아이템 생성 딜레이 값*/
	float SpawnDelay;
};
