// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WutheringWave/GameData/DataTable/WWCharacterStatTable.h"
#include "WutheringWave/GameData/DataTable/WWWeaponDataTable.h"
#include "WWDataTableIDSearchSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class WUTHERINGWAVE_API UWWDataTableIDSearchSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable, Category = "GetRow")
    bool GetCharacterStatRow(int32 ID, FWWCharacterStatTable& OutRow) const
    {
        return GetRow<FWWCharacterStatTable>(ID, OutRow);
    }

    UFUNCTION(BlueprintCallable, Category = "GetRow")
    bool GetWeaponDataRow(int32 ID, FWWWeaponDataTable& OutRow) const
    {
        return GetRow<FWWWeaponDataTable>(ID, OutRow);
    }
    
    template<typename T>
    const T* GetRow(int32 ID) const
    {
        UScriptStruct* Key = T::StaticStruct();

        const auto& IDMap = DataIDMaps.Find(Key);
        if (IDMap)
        {
            const FTableRowBase* const* FoundRow = IDMap->Find(ID);
            if (FoundRow)
            {
                return static_cast<const T*>(*FoundRow);
            }
        }

        return nullptr;
    }

private:
    template<typename T>
    bool GetRow(int32 ID, T& OutRow) const;

    template<typename T>
    void BuildIDMap(TObjectPtr<UDataTable> DataTable);

private:
    UPROPERTY(EditDefaultsOnly, Category = "DataTable")
    TObjectPtr<UDataTable> CharacterStatDataTable;
    
    UPROPERTY(EditDefaultsOnly, Category = "DataTable")
    TObjectPtr<UDataTable> WeaponDataTable;

    TMap<UScriptStruct*, TMap<int32, const FTableRowBase*>> DataIDMaps;
};
