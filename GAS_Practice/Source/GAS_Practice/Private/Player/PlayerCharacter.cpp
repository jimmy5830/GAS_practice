// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Arribute/GASAttributeSet.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GAS_Practice/AbilityInputID.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Enhanced Input: MappingContext 추가
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (IMC_Player)
				{
					Subsystem->AddMappingContext(IMC_Player, 0);
				}
			}
		}
	}

	InitASC();
}

void APlayerCharacter::GiveDefaultAbilities()
{
	if (!AbilitySystem || bAbilitiesGiven)
	{
		return;
	}

	if (AttackAbilityClass)
	{
		FGameplayAbilitySpec Spec(AttackAbilityClass, 1, static_cast<int32>(EAbilityInputID::Attack), this);
		AbilitySystem->GiveAbility(Spec);
	}

	bAbilitiesGiven = true;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Attack)
		{
			EIC->BindAction(IA_Attack, ETriggerEvent::Started, this, &APlayerCharacter::OnAttackInputPressed);
			EIC->BindAction(IA_Attack, ETriggerEvent::Completed, this, &APlayerCharacter::OnAttackInputReleased);
		}
	}
}

void APlayerCharacter::OnAttackInputPressed()
{
	if (!AbilitySystem) return;

	AbilitySystem->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Attack));
	AbilitySystem->TryActivateAbilityByClass(AttackAbilityClass); // 안전빵: 혹시 InputPressed만으로 활성화 안 될 때
}

void APlayerCharacter::OnAttackInputReleased()
{
	if (!AbilitySystem) return;

	AbilitySystem->AbilityLocalInputReleased(static_cast<int32>(EAbilityInputID::Attack));
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitASC();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitASC();
}

void APlayerCharacter::InitASC()
{
	// GAS: ASC 초기화
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
		GiveDefaultAbilities();
	}
}



