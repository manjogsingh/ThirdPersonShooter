// Created by Manjog Singh


#include "SGameModeBase.h"
#include "SHealthComponent.h"
#include "SGameStateBase.h"
#include "SPlayerState.h"

ASGameModeBase::ASGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	GameStateClass = ASGameStateBase::StaticClass();
	PlayerStateClass = ASPlayerState::StaticClass();

	TimeBetweenWaves = 2.0f;
}

void ASGameModeBase::StartWave()
{
	WaveCount++;
	SpawnNumber = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &ASGameModeBase::SpawnBotTimerElapsed, 1.0f, true, 0.0f);

	SetWaveState(EWaveState::WaveInProgress);
}

void ASGameModeBase::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);

	SetWaveState(EWaveState::WaitingToComplete);
}

void ASGameModeBase::PrepareForNextWave()
{
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &ASGameModeBase::StartWave, TimeBetweenWaves, false);

	SetWaveState(EWaveState::WaitingToStart);

	RespawnDeadPlayers();
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	SpawnNewBot();

	SpawnNumber--;

	if (SpawnNumber <= 0)
	{
		EndWave();
	}
}

void ASGameModeBase::CheckWaveStatus()
{
	bool bIsPreparingForWave = GetWorldTimerManager().IsTimerActive(TimerHandle_NextWaveStart);

	if (SpawnNumber > 0 || bIsPreparingForWave)
	{
		return;
	}

	bool bAnyBotAlive = false;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* TestPawn = It->Get();
		if (TestPawn == nullptr || TestPawn->IsPlayerControlled())
		{
			continue;
		}

		USHealthComponent* HealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
		if (HealthComp && HealthComp->GetHealth() > 0.0f)
		{
			bAnyBotAlive = true;
			break;
		}
	}

	if (!bAnyBotAlive)
	{
		SetWaveState(EWaveState::WaveComplete);

		PrepareForNextWave();
	}
}

void ASGameModeBase::CheckAnyPlayerAlive()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn())
		{
			APawn* MyPawn = PC->GetPawn();
			USHealthComponent* HealthComp = Cast<USHealthComponent>(MyPawn->GetComponentByClass(USHealthComponent::StaticClass()));
			if (ensure(HealthComp) && HealthComp->GetHealth() > 0)
			{
				return;
			}
		}
	}

	GameOver();
}

void ASGameModeBase::GameOver()
{
	EndWave();

	SetWaveState(EWaveState::GameOver);

	UE_LOG(LogTemp, Log, TEXT("DIED"));
}

void ASGameModeBase::SetWaveState(EWaveState NewState)
{
	ASGameStateBase* GS = GetGameState<ASGameStateBase>();
	if (ensureAlways(GS))
	{
		GS->SetWaveState(NewState);
	}
}

void ASGameModeBase::RespawnDeadPlayers()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{
			RestartPlayer(PC);
		}
	}
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}

void ASGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckWaveStatus();
	CheckAnyPlayerAlive();
}
