//
//  FloatingHealthBarWidgetComponent.cpp
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 02.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Health/FloatingHealthBarWidgetComponent.h"

UFloatingHealthBarWidgetComponent::UFloatingHealthBarWidgetComponent() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;
    // bReplicates = true;

    static ConstructorHelpers::FClassFinder<UFloatingHealthBarWidget> FloatingHealthBarWidget(TEXT("/UEWeaponSysBasePlugin/Widgets/FloatingHealthBarWidget"));
    
    if(FloatingHealthBarWidget.Class)
    {
        this->bEditableWhenInherited = true;
        this->SetWidgetClass(FloatingHealthBarWidget.Class);
        this->SetWidgetSpace(EWidgetSpace::World);
        // this->InitWidget();
        // this->FloatingHealthBar = Cast<UFloatingHealthBarWidget>(this->GetWidget());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("FloatingHealthBarWidget.Class IS NULL  ..."));
    }

    this->SetNetAddressable(); // Make DSO components net addressable
	this->SetIsReplicated(true);
    this->SetOwnerNoSee(true);
}

void UFloatingHealthBarWidgetComponent::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //Replicate current health.
    // DOREPLIFETIME(UFloatingHealthBarWidgetComponent, CurrentHealth);
}

void UFloatingHealthBarWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    // this->InitWidget();
    // ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    // if(Cast<AActor>(this->GetOwner()) == PlayerCharacter)
    // {
    //     this->SetVisibility(false);
    // }
}

void UFloatingHealthBarWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(this->IsWidgetVisible())
    {
        UHUDFunc::RotateToPlayer(Cast<USceneComponent>(this), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    }
}