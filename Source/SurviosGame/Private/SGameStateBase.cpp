// Created by Manjog Singh


#include "SGameStateBase.h"
#include "Net/UnrealNetwork.h"

void ASGameStateBase::OnRep_WaveState(EWaveState OldState)
{
	WaveStateChanged(WaveState, OldState);
}

void ASGameStateBase::SetWaveState(EWaveState NewState)
{
	if (Role == ROLE_Authority)
	{
		EWaveState OldState = WaveState;
		WaveState = NewState;

		OnRep_WaveState(OldState);
	}
}

EWaveState ASGameStateBase::GetWaveState()
{
	return WaveState;
}

void ASGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGameStateBase, WaveState);
}