// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SnakePart.h"

void ASnakeGameMode::BeginPlay()
{
	Super::BeginPlay();
	// [][][][][]
	// []      []
	// []      []
	// []      []
	// [][][][][]

	RandomCreate.GenerateNewSeed();

}

void ASnakeGameMode::CreateOutWall(int _Y, int _Z, FVector _TileSize, TSubclassOf<AActor> _WallType)
{
	// ��κδ��� �𸮾� ������ ������Ʈ���� ��� �ִ� 
	// 3���������� ��ġ���� �������ְ� ó���ϱ� ���ؼ� �ְ�޴� ����ü �Դϴ�.
	// F�� �پ������� ����ü
	// FTransform Trans;
	//TPersistentVectorRegisterType<T> Rotation; ȸ��
	//TPersistentVectorRegisterType<T> Translation; ��ġ
	//TPersistentVectorRegisterType<T> Scale3D; ũ��

	// s��Ƽ����Ʈ�� 
	UE_LOG(LogTemp, Log, TEXT("%S(%u)> MapCreate Start"), __FUNCTION__, __LINE__);

	TileCount.Y = _Y;
	TileCount.Z = _Z;

	TileSize = _TileSize;


	// 
	AllMapActor.SetNumZeroed(TileCount.Z);
	// Num() => size()
	for (size_t z = 0; z < AllMapActor.Num(); z++)
	{
		AllMapActor[z].SetNum(TileCount.Y);
	}
	// Wall::StaticClass() <= ���� ���� �����Ϸ��� ���Ͱ� ������ �˷��ݴϴ�.
	// �� ���ο��� �������Ʈ wall�� �˼� �־�� �Ѵ�.
	for (size_t i = 0; i < TileCount.Y; i++)
	{
		FTransform Trans;
		Trans.SetLocation({ 0, TileSize.Y * static_cast<float>(i), 0.0f });
		AActor* SpawnedActor0 = GetWorld()->SpawnActor<AActor>(_WallType, Trans);

		Trans.SetLocation({ 0, TileSize.Y * static_cast<float>(i), TileSize.Z * static_cast<float>(TileCount.Z - 1) });
		AActor* SpawnedActor1 = GetWorld()->SpawnActor<AActor>(_WallType, Trans);
	}

	for (size_t i = 0; i < TileCount.Z; i++)
	{
		FTransform Trans;
		Trans.SetLocation({ 0, 0, TileSize.Z * i });
		AActor* SpawnedActor0 = GetWorld()->SpawnActor<AActor>(_WallType, Trans);

		Trans.SetLocation({ 0, TileSize.Y * static_cast<float>(TileCount.Y - 1), TileSize.Z * i });
		AActor* SpawnedActor1 = GetWorld()->SpawnActor<AActor>(_WallType, Trans);
	}


}

void ASnakeGameMode::SetPart(AActor* _Part)
{
	// �迭������ x y�� �ɼ��� ����.
	//          200                       100

	FVector Pos = _Part->GetActorLocation();

	int Y = Pos.Y / TileSize.Y;
	int Z = Pos.Z / TileSize.Z;

	SetPart(Y, Z, _Part);

	// SetPart(, _Part);
}

void ASnakeGameMode::SetPart(int _Y, int _Z, AActor* _Part)
{
	if (0 > _Y)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return;
	}

	if (0 > _Z)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return;
	}

	if (_Y >= TileCount.Y)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (Y >= TileCount.Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return;
	}

	if (_Z >= TileCount.Z)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (Z >= TileCount.Z) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return;
	}

	AllMapActor[_Z][_Y] = _Part;
}

void ASnakeGameMode::Tick(float _Delta)
{
	Super::Tick(_Delta);

	// 1. ȭ���� �ʺ�� ���Ӹ�尡 �˾�.
	TileCount;

	// 2. ȭ�鳻�� �����ϴ� ��� SnakePart�� ��ӹ��� ���͵��� �˰� �;�.
	// ���� �ذ��ϴ� ����� ������ ����δ��� �ִ�.

	// ������ �����ϴ°� Ȯ���� �߸������ϰ� �ִ°���
	// ��� ���� ���� �����ϴ°� �翬�� ���� �ӷ��� ������ �ڵ��� ���̴�.
	TArray<AActor*> AllSnakeActor;
	//                                   �̷����� �ִ�  �� �±׸� ���� ���͸� AllSnakeActor�� �����
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "SnakePart", AllSnakeActor);
	// ������ ����� �ʹ�
	// => ������Ʈ�� �׷��� ����?
	// 1000�� �̻��ΰ�? 100�� �����ϰž�.
	// �׷� ��Ȳ���� ���ص� �������� �������� 

	// Fname�� ����Ѵ�.
	// "aaaaaa" "aaaaaab"
	// unreal�� �� ����ȭ�� ���ؼ� FName �ڷ����� �������.
	// FName�� "fasdhjkfasdhjkfasdjklfaskjlfasdjkl" => 223 �ؽ� ����̶�� �մϴ�.
	// FName�� ���ο��� ���ڿ��� ���� 1�� ¥���� �ٲ��ش�.
	// FName �񱳴� ���� ���Դϴ�.
	// ���ο� ���Ͱ� 100���� 

	AllMapClear();

	for (size_t i = 0; i < AllSnakeActor.Num(); i++)
	{
		SetPart(AllSnakeActor[i]);
	}

	if (nullptr == BodyType)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BodyType)"), __FUNCTION__, __LINE__);
		return;
	}

	if (nullptr == CurBody && nullptr != BodyType)
	{

		TArray<FIntVector> EmptyPoint;

		for (int z = 0; z < AllMapActor.Num(); z++)
		{
			for (int y = 0; y < AllMapActor[z].Num(); y++)
			{
				if (nullptr != AllMapActor[z][y])
				{
					continue;
				}

				EmptyPoint.Add({ 0, y, z });
			}
		}

		// ���ο��� seed�� �ð����� ó������� ��¥ ������ ��ġ�� ����Ҽ� �ִ�.

		// 0 63
		// �𸮾��� max���� �� ���ɴϴ�.
		int RandomIndex = RandomCreate.RandRange(0, EmptyPoint.Num() - 1);

		FIntVector PointVector = EmptyPoint[RandomIndex];

		FTransform Trans;

		Trans.SetLocation({ 0.0f, PointVector.Y * TileSize.Y, PointVector.Z * TileSize.Z });


		CurBody = GetWorld()->SpawnActor<AActor>(BodyType, Trans);
	}
}

void ASnakeGameMode::AllMapClear()
{
	for (size_t z = 0; z < AllMapActor.Num(); z++)
	{
		for (size_t y = 0; y < AllMapActor[z].Num(); y++)
		{
			AllMapActor[z][y] = nullptr;
		}
	}
}

bool ASnakeGameMode::IsPart(FVector _Pos, FName _Tag)
{
	int Y = _Pos.Y / TileSize.Y;
	int Z = _Pos.Z / TileSize.Z;

	AllMapActor;

	return IsPart(Y, Z, _Tag);
}

bool ASnakeGameMode::IsPart(int _Y, int _Z, FName _Tag)
{
	if (0 > _Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return false;
	}

	if (0 > _Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return false;
	}

	if (_Y >= TileCount.Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Y >= TileCount.Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return false;
	}

	if (_Z >= TileCount.Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Z >= TileCount.Z) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return false;
	}

	if (nullptr == AllMapActor[_Z][_Y])
	{
		return false;
	}

	return AllMapActor[_Z][_Y]->ActorHasTag(_Tag);
}

AActor* ASnakeGameMode::GetPart(FVector _Pos, FName _Tag)
{
	int Y = _Pos.Y / TileSize.Y;
	int Z = _Pos.Z / TileSize.Z;

	return GetPart(Y, Z, _Tag);
}

AActor* ASnakeGameMode::GetPart(int _Y, int _Z, FName _Tag)
{
	if (0 > _Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return nullptr;
	}

	if (0 > _Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (0 >= Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return nullptr;
	}

	if (_Y >= TileCount.Y)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Y >= TileCount.Y) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return nullptr;
	}

	if (_Z >= TileCount.Z)
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u)> if (Z >= TileCount.Z) [Y : %d][Z : %d]"), __FUNCTION__, __LINE__, _Y, _Z);
		return nullptr;
	}

	if (nullptr == AllMapActor[_Z][_Y])
	{
		return nullptr;
	}

	if (false == AllMapActor[_Z][_Y]->ActorHasTag(_Tag))
	{
		return nullptr;
	}

	return AllMapActor[_Z][_Y];
}

void ASnakeGameMode::CurBodyReset()
{
	CurBody = nullptr;
}