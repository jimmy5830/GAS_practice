#include "Enemy/EnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "Arribute/GASAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitASC();
}

void AEnemyCharacter::PossessedBy(AController* NewController)

{
	Super::PossessedBy(NewController);
	InitASC();
}

void AEnemyCharacter::InitASC()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
