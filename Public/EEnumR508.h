
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEnumR508 : uint8
{
    Weapon UMETA(DisplayName = "Weapon"),
    Part UMETA(DisplayName = "Part"),
    Food UMETA(DisplayName = "Food"),
    Armor UMETA(DisplayName = "Armor"),

};


UENUM(BlueprintType)
enum class ESecondTypeWeapon : uint8
{
    Rifle UMETA(DisplayName = "Rifle"),
    Pisto UMETA(DisplayName = "Pistol"),
    Hands UMETA(DisplayName = "Hands"),
    None UMETA(DisplayName = "None"),
};