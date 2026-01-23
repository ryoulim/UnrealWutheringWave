// Fill out your copyright notice in the Description page of Project Settings.


#include "WWRoleDevAnimInstance.h"

void UWWRoleDevAnimInstance::ReadyAnimSet(const TMap<EWWUIAnimName, FWWUIAnimSet>& InAnimSets)
{
	const FWWUIAnimSet* NatureSet = InAnimSets.Find(EWWUIAnimName::Nature);
	if (NatureSet)
	{
		NatureStartAnim = NatureSet->Start.Get();
		NatureLoopAnim = NatureSet->Loop.Get();
		NatureEndAnim = NatureSet->End.Get();
	}

	const FWWUIAnimSet* ChipSet = InAnimSets.Find(EWWUIAnimName::Chip);
	if (ChipSet)
	{
		ChipStartAnim = ChipSet->Start.Get();
		ChipLoopAnim = ChipSet->Loop.Get();
		ChipEndAnim = ChipSet->End.Get();
	}

	const FWWUIAnimSet* WeaponSet = InAnimSets.Find(EWWUIAnimName::Weapon);
	if (WeaponSet)
	{
		WeaponStartAnim = WeaponSet->Start.Get();
		WeaponLoopAnim = WeaponSet->Loop.Get();
		WeaponEndAnim = WeaponSet->End.Get();
	}

	const FWWUIAnimSet* ResonantSet = InAnimSets.Find(EWWUIAnimName::Resonant);
	if (ResonantSet)
	{
		ResonantStartAnim = ResonantSet->Start.Get();
		ResonantLoopAnim = ResonantSet->Loop.Get();
		ResonantEndAnim = ResonantSet->End.Get();
	}
}