// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WWSaveGameBase.h"
#include "WWAccountInformation.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FWWAccountInformation
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AccountData)
	FString Name = { TEXT("이름이름") };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AccountData)
	int32 UID = { 135792468 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AccountData)
	FIntPoint BirthDay = {1, 1};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayData)
	int32 Rank = { 1 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayData)
	int32 Level = { 1 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayData)
	int32 Exp = { 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UserWord)
	FString UserWord = { TEXT("상태메시지를 입력하세요") };
};

UCLASS()
class WUTHERINGWAVE_API UWWAccountSaveGame : public UWWSaveGameBase
{
	GENERATED_BODY()

public:
	const FWWAccountInformation* GetAccountInformation() const {
		return &AccountInformation;
	}
	UFUNCTION(BlueprintCallable)
	void SetName(const FString& InName) {
		AccountInformation.Name = InName;
		SaveData();
	}
	UFUNCTION(BlueprintCallable)
	void SetBirthDay(int32 Month, int32 Date) {
		AccountInformation.BirthDay = { Month, Date };
		SaveData();
	}
	UFUNCTION(BlueprintCallable)
	void SetRank(int32 InRank) {
		AccountInformation.Rank = InRank;
		SaveData();
	}
	UFUNCTION(BlueprintCallable)
	void AddExp(int32 InExp) {
		AccountInformation.Exp += InExp;
		if (AccountInformation.Exp >= 1000)
		{
			AccountInformation.Level += AccountInformation.Exp / 1000;
			AccountInformation.Exp %= 1000;
		}
		SaveData();
	}
	UFUNCTION(BlueprintCallable)
	void SetUserWord(const FString& InUserWord) {
		AccountInformation.UserWord = InUserWord;
		SaveData();
	}

private:
	UPROPERTY()
	FWWAccountInformation AccountInformation;
};