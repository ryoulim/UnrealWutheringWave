// Fill out your copyright notice in the Description page of Project Settings.


#include "WWDataTableIDSearchSubsystem.h"

void UWWDataTableIDSearchSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    BuildIDMap<FWWCharacterStatTable>(CharacterStatDataTable);
    BuildIDMap<FWWWeaponDataTable>(WeaponDataTable);
}

template<typename T>
bool UWWDataTableIDSearchSubsystem::GetRow(int32 ID, T& OutRow) const
{
    UScriptStruct* Key = T::StaticStruct();

    const auto& IDMap = DataIDMaps.Find(Key);
    if (IDMap)
    {
        const FTableRowBase* const* FoundRow = IDMap->Find(ID);
        if (FoundRow)
        {
            OutRow = *static_cast<const T*>(*FoundRow);
            return true;
        }
    }

    return false;
}

template<typename T>
void UWWDataTableIDSearchSubsystem::BuildIDMap(TObjectPtr<UDataTable> DataTable)
{
    check(DataTable);
    check(DataTable->GetRowStruct() == T::StaticStruct());

    UScriptStruct* Key = T::StaticStruct();
    DataIDMaps.Add(Key);
    auto& IDMap = DataIDMaps[Key];
    
    for (const auto& Pair : DataTable->GetRowMap())
    {
        const T* Row = reinterpret_cast<const T*>(Pair.Value);

        if (IDMap.Contains(Row->ID))
        {
            continue;
        }

        IDMap.Add(Row->ID, Row);
    }
}