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
	
	//Pickup.h�� �ִ� ���ø������̼� �Լ� �������̵�
	void WasCollected_Implementation() override;


	float GetPower();//���� ���͸��� �Ŀ� �� ���� �� ����.


protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Power",Meta=(BlueprintProtected="true"))
	float BatteryPower;//���͸��� ĳ���Ϳ��� ������ ��
};
