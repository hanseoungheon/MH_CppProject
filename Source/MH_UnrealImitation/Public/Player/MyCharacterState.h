#pragma once
#include "CoreMinimal.h"
#include "MyCharacterState.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    Peace = 0  UMETA(DisplayName = "Peace"),
    Battle = 1 UMETA(DisplayName = "Battle"),
    Draw = 2   UMETA(DisplayName = "Draw"),
    Sheath = 3 UMETA(DisplayName = "Sheath"),
    //Iai    UMETA(DisplayName = "Iai"),
    Roll = 4   UMETA(DisplayName = "Roll"),
    Dead = 5   UMETA(DisplayName = "Dead"),
};