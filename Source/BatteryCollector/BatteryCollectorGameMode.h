// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UserWidget.h"
#include "BatteryCollectorGameMode.generated.h"


//현재 게임플레이 상태를 저장하는 enum
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

	//게임 승리에 필요한 파워 알려줌 ui에 사용
	UFUNCTION(BlueprintPure,Category="Power")
		float GetPowerToWin();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category="Power")
		EBatteryPlayState GetCurrentState() const; //현재 상태로 돌아감

	void SetCurrentState(EBatteryPlayState NewState); //새로운 상태 설정
protected:
	//캐릭터 파워가 줄어드는 정도
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Power",Meta=(BlueprintProtected="true"))
		float DecayRate;


	//승리하기 위해 모아야하는 배터리양
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float PowerToWin;
	


	/*HUD 화면에 사용할 위젯 클래스*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	/*Hud 인스턴스*/
	UPROPERTY()
		class UUserWidget * CurrentWidget;

private:
	EBatteryPlayState CurrentState;//현재 캐릭터 상태


	TArray<class ASpawnVolume*> SpawnVolumeActors;


	/*게임 플레이 상태에 영향을 주는 모든함수의 호출을 담당*/
	void HandleNewState(EBatteryPlayState NewState);
};



