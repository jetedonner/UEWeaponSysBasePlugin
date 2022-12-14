// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Score/ScoreManagerComponent.h"

UScoreManagerComponent::UScoreManagerComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;
	this->SetIsReplicatedByDefault(true);
}

void UScoreManagerComponent::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UScoreManagerComponent, Score);
}

void UScoreManagerComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UScoreManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScoreManagerComponent::OnScoreUpdate()
{
	if (Cast<ACharacter>(this->GetOwner())->IsLocallyControlled())
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
	}

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
		Score = Value;
        OnScoreUpdate();
    }
}

void UScoreManagerComponent::AddScore(int32 Value)
{
    SetScore(Score + Value);
}

void UScoreManagerComponent::ResetScore()
{
    SetScore(0);
}