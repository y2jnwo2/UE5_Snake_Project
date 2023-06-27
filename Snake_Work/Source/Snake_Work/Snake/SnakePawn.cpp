// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();

	// ��� �̿��ϴ°��� ���� �Ϲ����̴�.
	// �𸮾󿡼� GameInstacne�� �Ϲ������� �̷� ������ �ְ�޴� �뵵�� ������ �༮�̴�.
	// GetGameInstance()

	// ���� �� ������ GameMode�� ����.
	// ������ �� ������ ���մϴ�.
	// �� ���� �� ������ ���õ� GameMode�� �˷��� �翬�� ������ �� Level�� �˾ƾ� 

	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	// �ٿ� ĳ��Ʈ�� �ؾ��մϴ�.
	if (nullptr == GameModePtr)
	{
		// �� TEXT�� ���ؼ��� �������ڸ�
		// �𸮾󿡼��� �����ڵ� ��Ƽ����Ʈ�� �������� �ʴ´�.
		// � �����ڵ�� �𸮾����� �˾Ƽ� ã���ش�.
		// ���ڿ��� �������� ���ڵ��� �ִ¿� �� ���ڵ��� �˾Ƽ� �ڽŵ��� ó���ϰڴٴ� �ǹ̷�
		// TEXT() �˾Ƽ� �����ڵ�� ��Ƽ����Ʈ�� ���� �˾Ƽ� �� ó���ϰڴ�.
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	// �𸮾��� ���̺귯���� �̳༮�� �ܼ��� nullptr�� �ƴ϶�� �� �����δ� �������� Ȯ���Ҽ�
	// ���ٰ� �����ؼ� ������ UObject�ȿ� �ɹ��Լ���
	// ���� ����Ϸ��� �𸮾��� UOBject�� ��ӹ��� �����Ͱ� �������� ���������� Ȯ���Ϸ���
	// �ܼ��� nullptr������ �ȵǰ� IsValidLowLevel �Լ��� ����ؼ� �𸮾��� ����� �������ְ� �ִ�
	// ���������� �˾Ƴ����� �ִ�.
	if (false == GameModePtr->IsValidLowLevel())
	{
		// �𸮾��� �˻�� �������ʹ� ������ ���ɼ��� �ִٴ°��̴�.
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	// �ٿ�ĳ����
	ASnakeGameMode* SnakeGameMode = Cast<ASnakeGameMode>(GameModePtr);

	if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return;
	}

	FIntVector3 Count = SnakeGameMode->GetCount();
	FVector Size = SnakeGameMode->GetTileSize();
	// /�� ��Ģ������ ���� ���� �����Դϴ�.
	// /2 �ҹٿ��� *0.5f

	FVector Center = { -1000.0f, Size.Y * Count.Y * 0.5f, Size.Z * Count.Z * 0.5f };

	SetActorLocation(Center);
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ���� ��ġ���� ���ؼ� ó���ϴ� �Լ�
	// AddActorLocalOffset

	// ���� ���� ��ġ�� ��� �Ǿ��ְ� �� ��ġ�� �̵��ض�

}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void ASnakePawn::HeadPositionToCenter()
{

	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	if (nullptr == GameModePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	if (false == GameModePtr->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	ASnakeGameMode* SnakeGameMode = Cast<ASnakeGameMode>(GameModePtr);

	if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return;
	}

	FIntVector3 Count = SnakeGameMode->GetCount();
	FIntVector3 CenterCount;
	// ������ 0.5�� ����.
	CenterCount.Y = (Count.Y) / 2;
	CenterCount.Z = (Count.Z) / 2;
	FVector Size = SnakeGameMode->GetTileSize();

	FVector Center = { 0.0f, Size.Y * CenterCount.Y, Size.Z * CenterCount.Z };

	Head->SetActorLocation(Center);
}
