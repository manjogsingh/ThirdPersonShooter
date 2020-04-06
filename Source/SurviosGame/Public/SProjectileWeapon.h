// Created by Manjog Singh

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SURVIOSGAME_API ASProjectileWeapon : public ASWeapon
{
	GENERATED_BODY()
	
protected:

	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = "ProjectileWeapon")
	TSubclassOf<AActor> ProjectileClass;
};
