// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePart.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"

// Sets default values
ASnakePart::ASnakePart()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("SnakePart");
}

// Called when the game starts or when spawned
void ASnakePart::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	if (nullptr == GameModePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	// ���� ���� ���ڷ� �� �ִ� ���ͺ��� ���߿� Tick�� ������.
	// ���� ���ε� GameModePtr���� ���߿� tick�� ������.
	AddTickPrerequisiteActor(GameModePtr);
}

// Called every frame
void ASnakePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



ASnakeGameMode* ASnakePart::GetSnakeGameMode()
{
	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	if (nullptr == GameModePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	if (false == GameModePtr->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ASnakeGameMode* SnakeGameMode = Cast<ASnakeGameMode>(GameModePtr);

	if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return SnakeGameMode;
}