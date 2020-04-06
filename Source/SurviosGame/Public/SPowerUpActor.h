// Created by Manjog Singh

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

UCLASS()
class SURVIOSGAME_API ASPowerUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	float PowerUpInterval;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	int32 TotalNoOfTicks;

	FTimerHandle TimerHandle_PowerUpTick;

	int32 TicksProcessed;
	
	UFUNCTION()
	void OnTickPowerUp();

	UPROPERTY(ReplicatedUsing=OnRep_PowerUpActive)
	bool bIsPowerUpActive;

	UFUNCTION()
	void OnRep_PowerUpActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnPowerUpActiveChanged(bool bNewIsActive);

public:	

	void ActivatePowerUp(AActor* ActivateFor);

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnActivated(AActor* ActivateFor);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnPowerUpTicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnExpired();
};
