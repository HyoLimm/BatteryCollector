// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"
#include "EngineUtils.h"
#include "BatteryCollector.h"
#include "GameFramework/Character.h"



ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	

	//캐릭터파워 줄어드는 정도
	DecayRate = 0.01f;
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	//모든 스폰볼륨 액터를 찾기
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	/*for (auto Actor : FoundActors) {
	ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
	if (SpawnVolumeActor) {
	SpawnVolumeActors.AddUique(SpawnVolumeActor); //여기가 안댐
	}
	}*/
	for (TActorIterator<ASpawnVolume> It(GetWorld()); It; ++It) {
		SpawnVolumeActors.Add(*It);
	}


	SetCurrentState(EBatteryPlayState::EPlaying);


	//목표점수 설정
	ABatteryCollectorCharacter * MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) {
		PowerToWin = (MyCharacter->GetInitialPower())*1.25f;
	}
	

	if (HUDWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}




}//end of BeginPlay



void ABatteryCollectorGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);	


	/*배터리 캐릭터가 사용가능인지*/
	ABatteryCollectorCharacter * MyCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter) {


		/*요구 치 이상 모으면 게임 승리!*/
		if (MyCharacter->GetCurrentPower() > PowerToWin) {
			SetCurrentState(EBatteryPlayState::EWon); 
		}//0이상일때 되게
		else if (MyCharacter->GetCurrentPower() > 0) {
		MyCharacter->UpdatePower(-DeltaTime * DecayRate*(MyCharacter->GetInitialPower()));
		}
		else if (MyCharacter->GetCurrentPower() <= 0) {
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
}

float ABatteryCollectorGameMode::GetPowerToWin()
{
	return PowerToWin;
}

EBatteryPlayState ABatteryCollectorGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryCollectorGameMode::SetCurrentState(EBatteryPlayState NewState){
	CurrentState = NewState;
	HandleNewState(CurrentState);
}




void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
	case EBatteryPlayState::EPlaying:
	{
		//스폰활성화
		for (ASpawnVolume * Volume : SpawnVolumeActors) {
			Volume->SetSpawingActive(true);
		}
		break;
	}
	case EBatteryPlayState::EGameOver: {
		//게임오버

		for (ASpawnVolume * Volume : SpawnVolumeActors) {
			Volume->SetSpawingActive(false);
		}

		//입력을 막고
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController) {
			PlayerController->SetCinematicMode(true,false,false,true,true);
		}
		//래그돌 효과
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

		if (MyCharacter) {
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
		
	}
	break;
	case EBatteryPlayState::EWon: {
		//게임승리
		for (ASpawnVolume * Volume : SpawnVolumeActors) {
			Volume->SetSpawingActive(false);
		}
		break;
	}
	default:
	case EBatteryPlayState::EUnknown:
		//알수없음
		break;



	}
}