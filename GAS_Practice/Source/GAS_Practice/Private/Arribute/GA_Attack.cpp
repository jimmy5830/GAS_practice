// Fill out your copyright notice in the Description page of Project Settings.


#include "Arribute/GA_Attack.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Actor.h"

UGA_Attack::UGA_Attack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Attack::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (ActorInfo && ActorInfo->AvatarActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[GAS] Attack Ability Activated by %s"), *ActorInfo->AvatarActor->GetName());
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

