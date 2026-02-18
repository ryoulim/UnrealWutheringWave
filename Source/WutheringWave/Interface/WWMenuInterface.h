// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WWMenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWWMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WUTHERINGWAVE_API IWWMenuInterface
{
	GENERATED_BODY()

public:
	virtual void OpenMenu() = 0;
	virtual void CloseMenu() = 0;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
