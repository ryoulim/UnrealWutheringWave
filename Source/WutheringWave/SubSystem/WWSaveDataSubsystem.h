// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WWSaveDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWSaveDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void LoadAllData();

	/* SaveGame */
public:
	class UWWAccountSaveGame* GetAccountSaveGame() const {
		return AccountSaveGame;
	}
	class UWWCharacterDevelopmentSaveGame* GetCharacterSaveGame() const {
		return CharacterSaveGame;
	}
	class UWWWeaponDevelopmentSaveGame* GetWeaponSaveGame() const {
		return WeaponSaveGame;
	}
	class UWWEcoDevelopmentSaveGame* GetEcoSaveGame() const {
		return EcoSaveGame;
	}
	class UWWWWInventoryDataSaveGame* GetInventorySaveGame() const {
		return InventorySaveGame;
	}
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
	TObjectPtr<class UWWAccountSaveGame> AccountSaveGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
	TObjectPtr<class UWWCharacterDevelopmentSaveGame> CharacterSaveGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
	TObjectPtr<class UWWEcoDevelopmentSaveGame> EcoSaveGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
	TObjectPtr<class UWWWWInventoryDataSaveGame> InventorySaveGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SaveGame)
	TObjectPtr<class UWWWeaponDevelopmentSaveGame> WeaponSaveGame;

private:
	bool bIsLoaded{};
};
