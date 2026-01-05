// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GAS_PRACTICE_API UGA_Attack : public UGameplayAbilitySet
{
	GENERATED_BODY()

public:
	UGA_Attack();

	// 간단 테스트용: ActivateAbility에서 로그만 찍고 끝내기
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;	
};
