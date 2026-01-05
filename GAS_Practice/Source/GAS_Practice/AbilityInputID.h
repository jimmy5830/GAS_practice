#pragma once
#include "AbilityInputID.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None   UMETA(DisplayName="None"),
	Attack UMETA(DisplayName="Attack"),
};
