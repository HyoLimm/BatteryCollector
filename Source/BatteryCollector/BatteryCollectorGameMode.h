// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UserWidget.h"
#include "BatteryCollectorGameMode.generated.h"


//���� �����÷��� ���¸� �����ϴ� enum
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8 {
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};


UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	//���� �¸��� �ʿ��� �Ŀ� �˷��� ui�� ���
	UFUNCTION(BlueprintPure,Category="Power")
		float GetPowerToWin();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category="Power")
		EBatteryPlayState GetCurrentState() const; //���� ���·� ���ư�

	void SetCurrentState(EBatteryPlayState NewState); //���ο� ���� ����
protected:
	//ĳ���� �Ŀ��� �پ��� ����
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Power",Meta=(BlueprintProtected="true"))
		float DecayRate;


	//�¸��ϱ� ���� ��ƾ��ϴ� ���͸���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float PowerToWin;
	


	/*HUD ȭ�鿡 ����� ���� Ŭ����*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	/*Hud �ν��Ͻ�*/
	UPROPERTY()
		class UUserWidget * CurrentWidget;

private:
	EBatteryPlayState CurrentState;//���� ĳ���� ����


	TArray<class ASpawnVolume*> SpawnVolumeActors;


	/*���� �÷��� ���¿� ������ �ִ� ����Լ��� ȣ���� ���*/
	void HandleNewState(EBatteryPlayState NewState);
};



