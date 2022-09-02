//
//  FloatingHealthBarWidget.cpp
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 14.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Health/FloatingHealthBarWidget.h"

void UFloatingHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UFloatingHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

// void UFloatingHealthBarWidget::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
// {
//     Super::GetLifetimeReplicatedProps(OutLifetimeProps);

//     //Replicate current health.
//     DOREPLIFETIME(UFloatingHealthBarWidget, Health);
// }

// void UFloatingHealthBarWidget::OnHealthUpdate()
// {
//     //Client-specific functionality
	
//     // if (Cast<ACharacter>(this->GetOwner())->IsLocallyControlled())
//     // {
//         FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), Health);
//         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, healthMessage);

//         // if (CurrentHealth <= 0)
//         // {
//         //     FString deathMessage = FString::Printf(TEXT("You have been killed."));
//         //     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
//         // }

// 		// if(this->FloatingHealthBar)
// 		// {
// 		// 	this->FloatingHealthBar->Health = CurrentHealth;
// 		// }
//     // }

//     //Server-specific functionality
//     // if (this->GetOwner()->GetLocalRole() == ROLE_Authority)
//     // {
//         FString healthMessage2 = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), Health);
//         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, healthMessage2);
//     // }

//     //Functions that occur on all machines. 
//     /*  
//         Any special functionality that should occur as a result of damage or death should be placed here. 
//     */
   	
// }

// void UFloatingHealthBarWidget::OnRep_Health()
// {
//     OnHealthUpdate();
// }