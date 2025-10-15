#pragma once
#include "CoreMinimal.h"
#include "MyCharacterState.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    Peace  UMETA(DisplayName = "Peace"),
    Battle UMETA(DisplayName = "Battle"),
    Draw   UMETA(DisplayName = "Draw"),
    Sheath UMETA(DisplayName = "Sheath"),
    //Iai    UMETA(DisplayName = "Iai"),
    Dead   UMETA(DisplayName = "Dead"),
};