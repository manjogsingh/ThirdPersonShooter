// Created by Manjog Singh


#include "SProjectileWeapon.h"

void ASProjectileWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner && ProjectileClass) {
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector MuzzleLocation = MeshComponent->GetSocketLocation(MuzzleSocketName);
		// FRotator MuzzleRotation = MeshComponent->GetSocketRotation(MuzzleSocketName);

		FActorSpawnParameters SpawnParmas;
		SpawnParmas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation, SpawnParmas);
	}
}
