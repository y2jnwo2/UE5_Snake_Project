// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SnakeGameMode.generated.h"

/**
 *
 */
UCLASS()
class SNAKE_WORK_API ASnakeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// �����ϸ鼭 ���� �ܰ� ���� ����� ���� �����ϴ� �Լ�
	// UFUNCTION �̰� �������Ʈ���� �� �Լ���.
	// BlueprintCallable => �������Ʈ���� ȣ�⵵ �ҰŴ�.
	// ���� C++���� ���� �Լ��� �𸮾� �����Ϳ��� ����ϱ� ���� ���
	UFUNCTION(BlueprintCallable)
		void CreateOutWall(int _Y, int _Z, FVector _TileSize, TSubclassOf<AActor> _WallType);

	FORCEINLINE FVector GetTileSize()
	{
		return TileSize;
	}

	FORCEINLINE FIntVector3 GetCount()
	{
		return TileCount;
	}

	void SetPart(class AActor* _Part);

	void SetPart(int _Y, int _Z, class AActor* _Part);

	bool IsPart(FVector _Pos, FName _Tag);

	bool IsPart(int _Y, int _Z, FName _Tag);

	AActor* GetPart(FVector _Pos, FName _Tag);

	AActor* GetPart(int _Y, int _Z, FName _Tag);

	void CurBodyReset();

protected:
	void BeginPlay() override;
	void Tick(float _Delta) override;

private:
	FVector TileSize;
	FIntVector3 TileCount;

	// std::vector<AActor*>

	// WeWeWeWeWeWeWeWeWe
	// We[][][]HE[][][]We
	// We[][][]HE[][][]We
	// We[][][]HE[][][]We
	// We[][][]HE[][][]We
	// We[][][][][][][]We
	// We[][][][][][][]We
	// WeWeWeWeWeWeWeWeWe
	// AllMapActor.Clear();

	TArray<TArray<class AActor*>> AllMapActor;

	void AllMapClear();

	AActor* CurBody = nullptr;

	FRandomStream RandomCreate = FRandomStream();


	// �̹����� ������ �������Ʈ���� �����ϰ� �����ϰ� �ʹ�.
	UPROPERTY(Category = "GameModeValue", EditAnywhere, DisplayName = "�ٵ� ������Ʈ Ŭ����")
		TSubclassOf<AActor> BodyType;

	UPROPERTY(Category = "GameModeValue", EditAnywhere, DisplayName = "�׳� �׽�Ʈ�� ����")
		int Value;
};
