// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"




ABatteryPickup::ABatteryPickup() {
	GetMesh()->SetSimulatePhysics(true);
	BatteryPower = 150.0f;


}
/////////////////////////////////////////////////////////////////

void ABatteryPickup::WasCollected_Implementation()
{
	//pickup�� ���̽��� ���
	Super::WasCollected_Implementation();
	//�׸��� �ı�
	Destroy();

}

float ABatteryPickup::GetPower()
{
	return BatteryPower; //���͸� �� ��������
}