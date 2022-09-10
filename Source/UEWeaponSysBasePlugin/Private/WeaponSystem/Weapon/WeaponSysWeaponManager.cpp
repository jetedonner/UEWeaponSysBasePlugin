//
//  WeaponSysWeaponManager.cpp
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 08.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Weapon/WeaponSysWeaponManager.h"

// Sets default values for this component's properties
UWeaponSysWeaponManager::UWeaponSysWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponSysWeaponManager::BeginPlay()
{
	Super::BeginPlay();
   
    int32 idx = 0;
    for(TSubclassOf<UWeaponSysWeaponBase> Weapon: WeaponArsenal)
    {
        if(Weapon)
        {
            UWeaponSysWeaponBase* NewWeapon = Cast<UWeaponSysWeaponBase>(Weapon->GetDefaultObject());
            
            UWeaponSysWeaponBase* NewWeaponImpl = NewObject<UWeaponSysWeaponBase>(this, NewWeapon->GetClass(), *NewWeapon->GetClass()->GetName());

            // NewWeaponImpl->MuzzleOffset = MuzzleOffset;
            // NewWeaponImpl->OnShotFiredDelegate.AddDynamic(this, &UWeaponSysWeaponManager::OnShotFired);        
            // NewWeaponImpl->OnWeaponReloading.AddDynamic(this, &UWeaponSysWeaponManager::WeaponReloading);

    //        NewWeaponImpl->OnProjectileFireDelegate.AddDynamic(this, &UWeaponManagerComponentBase::ProjectileFired);
    //        NewWeaponImpl->OnProjectileHitDelegate.AddDynamic(this, &UWeaponManagerComponentBase::ProjectileHit);

            NewWeaponImpl->RegisterComponent();
            WeaponArsenalImpl.AddUnique(NewWeaponImpl);
            if(idx == 0)
            {
                SetCurrentWeapon(NewWeaponImpl->WeaponDefinition()->WeaponID);
            }
            idx++;
        }
    }
    // this->SetComponentTickInterval(0.05f);
}

void UWeaponSysWeaponManager::PickupWeapon(int32 WeaponID, int32 AmmoCount)
{
    UWeaponSysWeaponBase* const* FoundWeapon = WeaponArsenalImpl.FindByPredicate( [&](UWeaponSysWeaponBase* Result){ return WeaponID == Result->WeaponDefinition()->WeaponID;} );
    if(FoundWeapon)
    {
        // UDbg::DbgMsg(FString::Printf(TEXT("PickupWeapon EXISTS AND FOUND")), 5.0f, FColor::Green);
        if(AmmoCount >= 0)
        {
            (*FoundWeapon)->AmmoCount += AmmoCount;
        }
        
        if(CurrentWeapon->WeaponDefinition()->WeaponID != WeaponID)
        {
            // IsAimedAtChar = false;
            // IsAimedAtHitable = false;
            // IsAimedAtPickup = false;
            if(CurrentWeapon->IsShooting)
            {
                CurrentWeapon->StopShooting();
            }
        }
        
        // SetCurrentWeapon(WeaponID, false);
    }
}

// Called every frame
void UWeaponSysWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponSysWeaponManager::SetCurrentWeapon(int32 WeaponID, bool PlayAudio)
{
    UDbg::DbgMsg(FString::Printf(TEXT("Setting current weapon")), 5.0f, FColor::Green);

    if(!CurrentWeapon || CurrentWeapon->WeaponDefinition()->WeaponID != WeaponID)
    {
//        IsAimedAtChar = false;
//        IsAimedAtHitable = false;
//        IsAimedAtPickup = false;
        for(UWeaponSysWeaponBase* Weapon: WeaponArsenalImpl)
        {
            if(Weapon->WeaponDefinition()->WeaponID == WeaponID)
            {
//                if(IsReloading)
//                {
//                    IsReloading = false;
//                }
//
//                if(IsShooting)
//                {
//                    GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
//                }

                CurrentWeapon = Weapon;

                AWeaponSysHUDBase* WeaponSystemHUD = Cast<AWeaponSysHUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
                if(WeaponSystemHUD)
                {   
                    // if(WeaponSystemHUD->CrosshairUserWidget)
                    // {
                    //     WeaponSystemHUD->CrosshairUserWidget->ShowCrosshair(WeaponID);
                    // }

                    if(WeaponSystemHUD->InfoHUDWidget)
                    {
                        WeaponSystemHUD->InfoHUDWidget->WeaponDefinition = *CurrentWeapon->WeaponDefinition();
                        WeaponSystemHUD->InfoHUDWidget->AmmoCountTotal = CurrentWeapon->AmmoCount;
                        WeaponSystemHUD->InfoHUDWidget->AmmoCountClip = CurrentWeapon->GetClipAmmoCount();
                    }
                    else
                    {
                        UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD->InfoHUDWidget IS NULL")), 5.0f, FColor::Green);
                    }
                }
                else
                {
                    UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD IS NULL")), 5.0f, FColor::Green);
                }
//
//                AWeaponSystemCharacterBase* MyOwner = Cast<AWeaponSystemCharacterBase>(this->GetOwner());
//                if(CurrentWeapon && MyOwner && MyOwner->IsPlayerControlled())
//                {
//                    if(CurrentCSWidget)
//                    {
//                        CurrentCSWidget->RemoveFromViewport();
//                        CurrentCSWidget->Destruct();
//
//                        UDbg::DbgMsg(FString::Printf(TEXT("Removing Current CS Widget")), 5.0f, FColor::Green);
//                    }
//
//                    TSubclassOf<class UUserWidget> CSWidgetClass = CurrentWeapon->WeaponDefinition()->CrosshairUserWidget;
//
//                        if(CSWidgetClass)
//                        {
//                            UDbg::DbgMsg(FString::Printf(TEXT("HAS New CS Widget")), 5.0f, FColor::Green);
//
//                            CurrentCSWidget = CreateWidget<UUserWidget>(GetWorld(), CSWidgetClass);
//                            if (CurrentCSWidget)
//                            {
//                                UDbg::DbgMsg(FString::Printf(TEXT("Adding Current CS Widget")), 5.0f, FColor::Green);
//                                CurrentCSWidget->AddToViewport();
//                            }
//                        }
//                }
//
//                if(WeaponChangeSound && PlayAudio)
//                {
//                    UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, this->WeaponChangeSound, GetOwner()->GetActorLocation(), FRotator::ZeroRotator, 2.0, 1.0, 0.0f, nullptr, nullptr, true);
//                }
                break;
            }
        }
    }
}