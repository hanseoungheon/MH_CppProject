#pragma once
#include "CoreMinimal.h"
#include "MyMonsterState.generated.h"


UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Peace    UMETA(DisplayName = "Peace"),
	Chase    UMETA(DisplayName = "Chase"),
	Roar     UMETA(DisplayName = "Roar"),
	Patrol   UMETA(DisplayName = "Patrol"),
	Dead     UMETA(DisplayName = "Dead"),
};