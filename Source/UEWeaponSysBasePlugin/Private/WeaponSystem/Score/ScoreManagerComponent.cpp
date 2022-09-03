// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Score/ScoreManagerComponent.h"

// Sets default values for this component's properties
UScoreManagerComponent::UScoreManagerComponent() : Super()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	this->SetIsReplicatedByDefault(true);
	// ...
}

void UScoreManagerComponent::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UScoreManagerComponent, Score);
}

// Called when the game starts
void UScoreManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScoreManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UScoreManagerComponent::OnScoreUpdate()
{
	UDbg::DbgMsg(FString::Printf(TEXT("New score is: %d."), Score), 5.0f, FColor::Green);

	ACharacter* OwnerCharacter = Cast<ACharacter>(this->GetOwner());
	if(OwnerCharacter)
	{
		APlayerController* WeaponSysBasePlayerController = Cast<APlayerController>(OwnerCharacter->Controller);
		if(WeaponSysBasePlayerController)
		{
			AWeaponSysHUDBase* WeaponSystemHUD = Cast<AWeaponSysHUDBase>(WeaponSysBasePlayerController->MyHUD);//Cast<APlayerController>(OwnerCharacter->GetController())->GetHUD());
			if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
			{   
				WeaponSystemHUD->InfoHUDWidget->Score = Score;
				// UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD->InfoHUDWidget->Score = Score!!!!")), 5.0f, FColor::Red);
			}
			else
			{
				UDbg::DbgMsg(FString::Printf(TEXT("SCORE: WeaponSystemHUD->InfoHUDWidget NOT Found!")), 5.0f, FColor::Red);
			}
		}
		else
		{
			UDbg::DbgMsg(FString::Printf(TEXT("SCORE: WeaponSysBasePlayerController NOT Found!")), 5.0f, FColor::Red);
		}
	}
	// AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
	// {
	// 	WeaponSystemHUD->InfoHUDWidget->Score = Score;
	// }

    //Client-specific functionality
	
    // if (Cast<ACharacter>(this->GetOwner())->IsLocallyControlled())
    // {
    //     // FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
    //     // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, healthMessage);

	// 	UDbg::DbgMsg(FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth), 5.0f, FColor::Green);

    //     if (CurrentHealth <= 0)
    //     {
    //         // FString deathMessage = FString::Printf(TEXT("You have been killed."));
    //         // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
	// 		UDbg::DbgMsg(FString::Printf(TEXT("You have been killed.")), 5.0f, FColor::Red);
    //     }
    // }

    // //Server-specific functionality
    // if (this->GetOwner()->GetLocalRole() == ROLE_Authority)
    // {
    //     // FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetOwner()->GetFName().ToString(), CurrentHealth);
    //     // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, healthMessage);
	// 	UDbg::DbgMsg(FString::Printf(TEXT("%s now has %f health remaining."), *GetOwner()->GetFName().ToString(), CurrentHealth), 5.0f, FColor::Purple);
    // }

    // //Functions that occur on all machines. 
    // /*  
    //     Any special functionality that should occur as a result of damage or death should be placed here. 
    // */
   	// if(this->FloatingHealthBar)
	// {
	// 	this->FloatingHealthBar->Health = CurrentHealth;
	// }else
	// {
	// 	// FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining. this->FloatingHealthBar IS NULL"), *GetOwner()->GetFName().ToString(), CurrentHealth);
    //     // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, healthMessage);
	// 	UDbg::DbgMsg(FString::Printf(TEXT("%s now has %f health remaining. this->FloatingHealthBar IS NULL"), *GetOwner()->GetFName().ToString(), CurrentHealth), 5.0f, FColor::Purple);
	// }
}

void UScoreManagerComponent::OnRep_Score()
{
    OnScoreUpdate();
}

void UScoreManagerComponent::SetScore(int32 Value)
{
	if (this->GetOwner()->GetLocalRole() == ROLE_Authority)
    {
        // CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
		Score = Value;
        OnScoreUpdate();
    }
	// AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
	// {
	// 	WeaponSystemHUD->InfoHUDWidget->Score = Score;
	// }	
}

void UScoreManagerComponent::AddScore(int32 Value)
{
    SetScore(Score + Value);
}

void UScoreManagerComponent::ResetScore()
{
    SetScore(0);
}