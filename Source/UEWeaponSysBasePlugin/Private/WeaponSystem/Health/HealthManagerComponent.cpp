//
//  HealthManagerComponent.cpp
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 02.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Health/HealthManagerComponent.h"

UHealthManagerComponent::UHealthManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// bReplicates = true;

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

	this->FloatingHealthBarWidgetComponentInst = this->GetOwner()->FindComponentByClass<UFloatingHealthBarWidgetComponent>();
	if(this->FloatingHealthBarWidgetComponentInst)
	{
		this->FloatingHealthBarWidgetComponentInst->InitWidget();
		if(this->FloatingHealthBarWidgetComponentInst->GetWidget())
		{
			UFloatingHealthBarWidget* MyFloatingHealthBarWidget = Cast<UFloatingHealthBarWidget>(this->FloatingHealthBarWidgetComponentInst->GetWidget());
			if(MyFloatingHealthBarWidget)
			{
				this->FloatingHealthBar = MyFloatingHealthBarWidget;
			}
		}
		else
		{
			UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidget NOT SET")), 5.0f, FColor::Green);
			
			// if(this->FloatingHealthBarWidgetComponentInst->FloatingHealthBar)
			// {
			// 	this->FloatingHealthBar = this->FloatingHealthBarWidgetComponentInst->FloatingHealthBar;
			// 	UDbg::DbgMsg(FString::Printf(TEXT("this->FloatingHealthBarWidgetComponentInst->FloatingHealthBar IIIISSSS SET")), 5.0f, FColor::Green);
			// }
			// else
			// {
			// 	UDbg::DbgMsg(FString::Printf(TEXT("this->FloatingHealthBarWidgetComponentInst->FloatingHealthBar NOT SET")), 5.0f, FColor::Green);
			// }
		}
	}
	else
	{
		UDbg::DbgMsg(FString::Printf(TEXT("FloatingHealthBarWidgetComponentInst NOT SET")), 5.0f, FColor::Purple);
	}
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
        // FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
        // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, healthMessage);

		UDbg::DbgMsg(FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth), 5.0f, FColor::Green);

        if (CurrentHealth <= 0)
        {
            // FString deathMessage = FString::Printf(TEXT("You have been killed."));
            // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
			UDbg::DbgMsg(FString::Printf(TEXT("You have been killed.")), 5.0f, FColor::Red);
        }
    }

    //Server-specific functionality
    if (this->GetOwner()->GetLocalRole() == ROLE_Authority)
    {
        // FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetOwner()->GetFName().ToString(), CurrentHealth);
        // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, healthMessage);
		UDbg::DbgMsg(FString::Printf(TEXT("%s now has %f health remaining."), *GetOwner()->GetFName().ToString(), CurrentHealth), 5.0f, FColor::Purple);
    }

    //Functions that occur on all machines. 
    /*  
        Any special functionality that should occur as a result of damage or death should be placed here. 
    */
   	if(this->FloatingHealthBar)
	{
		this->FloatingHealthBar->Health = CurrentHealth;
	}else
	{
		// FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining. this->FloatingHealthBar IS NULL"), *GetOwner()->GetFName().ToString(), CurrentHealth);
        // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, healthMessage);
		UDbg::DbgMsg(FString::Printf(TEXT("%s now has %f health remaining. this->FloatingHealthBar IS NULL"), *GetOwner()->GetFName().ToString(), CurrentHealth), 5.0f, FColor::Purple);
	}

	ACharacter* OwnerCharacter = Cast<ACharacter>(this->GetOwner());
	if(OwnerCharacter)
	{
		APlayerController* WeaponSysBasePlayerController = Cast<APlayerController>(OwnerCharacter->Controller);
		if(WeaponSysBasePlayerController)
		{
			AWeaponSysHUDBase* WeaponSystemHUD = Cast<AWeaponSysHUDBase>(WeaponSysBasePlayerController->MyHUD);//Cast<APlayerController>(OwnerCharacter->GetController())->GetHUD());
			if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
			{   
				WeaponSystemHUD->InfoHUDWidget->Health = CurrentHealth;
				// UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD->InfoHUDWidget->Score = Score!!!!")), 5.0f, FColor::Red);
			}
			else
			{
				UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD->InfoHUDWidget NOT Found!")), 5.0f, FColor::Red);
			}
		}
		else
		{
			UDbg::DbgMsg(FString::Printf(TEXT("WeaponSysBasePlayerController NOT Found!")), 5.0f, FColor::Red);
		}
	}
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