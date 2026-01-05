// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GAS_Practice/AbilityInputID.h"
#include "PlayerCharacter.generated.h"

class UGameplayAbility;
class UGASAttributeSet;
class UAbilitySystemComponent;
class UInputMappingContext;
class uInputAction;
class uGA_Attack;

UCLASS()
class GAS_PRACTICE_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category="GAS")
	UGASAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnAttackInputPressed();
	void OnAttackInputReleased();

	void GiveDefaultAbilities();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	void InitASC();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UGASAttributeSet> AttributeSet;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	// 공격 어빌리티 클래스(블루프린트에서 지정 가능)
	UPROPERTY(EditDefaultsOnly, Category="GAS|Abilities")
	TSubclassOf<UGameplayAbility> AttackAbilityClass;

	// Enhanced Input
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC_Player;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> IA_Attack;

	bool bAbilitiesGiven = false;

};
