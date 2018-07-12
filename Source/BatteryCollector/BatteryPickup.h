// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Pickup.h"
//#include "Components/SphereComponent.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	ABatteryPickup();
	
	//Pickup.h에 있는 임플리멘테이션 함수 오버라이딩
	void WasCollected_Implementation() override;


	float GetPower();//어디든 배터리의 파워 값 얻을 수 있음.


protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Power",Meta=(BlueprintProtected="true"))
	float BatteryPower;//배터리가 캐릭터에게 보내는 양
};
