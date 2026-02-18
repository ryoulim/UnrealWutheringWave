#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WWDataTableBase.generated.h"

USTRUCT(BlueprintType)
struct FWWDataTableBase : public FTableRowBase
{
	GENERATED_BODY()

	/* System */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = System)
	int32 ID;
};
