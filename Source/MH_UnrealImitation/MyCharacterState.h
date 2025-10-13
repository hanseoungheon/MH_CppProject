#pragma once
#include "CoreMinimal.h"
#include "MyCharacterState.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    Peace  UMETA(DisplayName = "Peace"),
    Battle UMETA(DisplayName = "Battle"),
    Dead   UMETA(DisplayName = "Dead"),
};