// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"
#include "Headers/WWEnums.h"
#include "Headers/WWMacros.h"
#include "WWRoleDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FWWUIAnimSet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AssetBundles = "UIAnimation"))
	TSoftObjectPtr<class UAnimSequence> Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AssetBundles = "UIAnimation"))
	TSoftObjectPtr<UAnimSequence> Loop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AssetBundles = "UIAnimation"))
	TSoftObjectPtr<UAnimSequence> End;
};

UCLASS()
class WUTHERINGWAVE_API UWWRolePropDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	friend class UWWRoleDataAsset;
	void AddLoadRequest(TArray<FSoftObjectPath>& AssetsToLoad)
	{
		AssetsToLoad.Add(Mesh.ToSoftObjectPath());
		for (auto& [Key, Value] : AnimSets)
		{
			AssetsToLoad.Add(Value.Start.ToSoftObjectPath());
			AssetsToLoad.Add(Value.Loop.ToSoftObjectPath());
			AssetsToLoad.Add(Value.End.ToSoftObjectPath());
		}
	}
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AssetBundles = "Mesh"))
	TSoftObjectPtr<class USkeletalMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AssetBundles = "UIAnimation"))
	TMap<EWWUIAnimName, FWWUIAnimSet> AnimSets;
};

/**
 * 
 */
UCLASS()
class WUTHERINGWAVE_API UWWRoleDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	WWDECLARE_DATAASSET_INT32(UWWRoleDataAsset, Role)
	UPROPERTY(EditDefaultsOnly, Category = "ID")
	int32 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoleClass")
	TSubclassOf<class AWWRoleBase> RoleClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoleClass")
	TSubclassOf<class AWWRoleDevActor> PreviewClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AssetBundles = "Mesh"))
	TSoftObjectPtr<class USkeletalMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AssetBundles = "UIAnimation"))
	TMap<EWWUIAnimName, FWWUIAnimSet> AnimSets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AssetBundles = "UITexture"))
	TSoftObjectPtr<class UTexture2D> UITexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AssetBundles = "Mesh"))
	TArray<TObjectPtr<class UWWRolePropDataAsset>> Props;

	TSharedPtr<FStreamableHandle> LoadPropsAssets(const FSimpleDelegate& LoadEndDelegate) const
	{
		TArray<FSoftObjectPath> AssetsToLoad;
		for (auto& Prop : Props)
		{
			Prop->AddLoadRequest(AssetsToLoad);
		}

		if(AssetsToLoad.IsEmpty())
		{
			LoadEndDelegate.ExecuteIfBound();
		}
		else
		{
			FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
			return Streamable.RequestAsyncLoad(AssetsToLoad, LoadEndDelegate);
		}

		return nullptr;
	}
};