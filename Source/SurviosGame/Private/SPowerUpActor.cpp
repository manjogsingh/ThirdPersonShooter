// Created by Manjog Singh


#include "SPowerUpActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerUpInterval = 0.0f;
	TotalNoOfTicks = 0.0f;

	bIsPowerUpActive = false;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASPowerUpActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASPowerUpActor::ActivatePowerUp(AActor* ActivateFor)
{
	OnActivated(ActivateFor);

	bIsPowerUpActive = true;
	OnRep_PowerUpActive();

	if (PowerUpInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTick, this, &ASPowerUpActor::OnTickPowerUp, PowerUpInterval, true);
	}
	else
	{
		OnTickPowerUp();
	}
}

void ASPowerUpActor::OnTickPowerUp()
{
	TicksProcessed++;

	OnPowerUpTicked();

	if (TotalNoOfTicks <= TicksProcessed)
	{
		OnExpired();

		bIsPowerUpActive = false;
		OnRep_PowerUpActive();

		GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTick);
	}
}

void ASPowerUpActor::OnRep_PowerUpActive()
{
	OnPowerUpActiveChanged(bIsPowerUpActive);
}

void ASPowerUpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUpActor, bIsPowerUpActive);
}