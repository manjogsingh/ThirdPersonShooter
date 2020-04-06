// Created by Manjog Singh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

enum class EWaveState : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);

/**
 * 
 */
UCLASS()
class SURVIOSGAME_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void SpawnNewBot();

	FTimerHandle TimerHandle_BotSpawner;
	FTimerHandle TimerHandle_NextWaveStart;

	int32 SpawnNumber;
	int32 WaveCount;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	float TimeBetweenWaves;

	void StartWave();
	void EndWave();
	void PrepareForNextWave();
	void SpawnBotTimerElapsed();
	void CheckWaveStatus();
	void CheckAnyPlayerAlive();
	void GameOver();

	void SetWaveState(EWaveState NewState);

	void RespawnDeadPlayers();

public:

	ASGameModeBase();

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnActorKilled OnActorKilled;
};
