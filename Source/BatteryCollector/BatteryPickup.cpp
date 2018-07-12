// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"




ABatteryPickup::ABatteryPickup() {
	GetMesh()->SetSimulatePhysics(true);
	BatteryPower = 150.0f;


}
/////////////////////////////////////////////////////////////////

void ABatteryPickup::WasCollected_Implementation()
{
	//pickup을 베이스로 사용
	Super::WasCollected_Implementation();
	//그리고 파괴
	Destroy();

}

float ABatteryPickup::GetPower()
{
	return BatteryPower; //배터리 값 가져오기
}
