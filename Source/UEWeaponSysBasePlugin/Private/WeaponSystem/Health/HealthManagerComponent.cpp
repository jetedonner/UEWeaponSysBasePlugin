// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSystem/Health/HealthManagerComponent.h"

UHealthManagerComponent::UHealthManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

void UHealthManagerComponent::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //Replicate current health.
    DOREPLIFETIME(UHealthManagerComponent, CurrentHealth);
}

// Called when the game starts
void UHealthManagerComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UHealthManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthManagerComponent::OnHealthUpdate()
{
    //Client-specific functionality
	
    if (Cast<ACharacter>(this->GetOwner())->IsLocallyControlled())
    {
        FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

        if (CurrentHealth <= 0)
        {
            FString deathMessage = FString::Printf(TEXT("You have been killed."));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
        }
    }

    //Server-specific functionality
    if (this->GetOwner()->GetLocalRole() == ROLE_Authority)
    {
        FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
    }

    //Functions that occur on all machines. 
    /*  
        Any special functionality that should occur as a result of damage or death should be placed here. 
    */
}

float UHealthManagerComponent::ApplyDamage(float DamageTaken)
{
	float DamageApplied = CurrentHealth - DamageTaken;
    SetCurrentHealth(DamageApplied);
    return DamageApplied;
}

void UHealthManagerComponent::OnRep_CurrentHealth()
{
    OnHealthUpdate();
}

void UHealthManagerComponent::SetCurrentHealth(float healthValue)
{
    if (this->GetOwner()->GetLocalRole() == ROLE_Authority)
    {
        CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
        OnHealthUpdate();
    }
}