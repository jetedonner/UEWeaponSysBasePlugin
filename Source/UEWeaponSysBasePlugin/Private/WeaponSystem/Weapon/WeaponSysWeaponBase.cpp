//
//  WeaponSysWeaponBase.cpp
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 08.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Weapon/WeaponSysWeaponBase.h"

// Sets default values
UWeaponSysWeaponBase::UWeaponSysWeaponBase():Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;
	PrimaryComponentTick.bCanEverTick = true;

}

UWeaponSysWeaponBase::UWeaponSysWeaponBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UWeaponSysWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

FWeaponDefinition* UWeaponSysWeaponBase::WeaponDefinition()
{
    if(WeaponDefinitionRowHandle.IsNull())
    {
        UDbg::DbgMsg(FString::Printf(TEXT("NO WeaponDefinition setup!")));
        // TODO: Return something that doesn't throw an exception
        return WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(WeaponDefinitionRowHandle.RowName, "");
    }
    else
    {
        return WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(WeaponDefinitionRowHandle.RowName, "");
    }
}

void UWeaponSysWeaponBase::StartShooting(EWeaponFunction WeaponFunction)
{
    if(WeaponDefinitionRowHandle.IsNull())
    {
        UDbg::DbgMsg(FString::Printf(TEXT("NO WeaponDefinition setup!")));
    }
    else
    {
        //UDbg::DbgMsg(FString::Printf(TEXT("WeaponDefinition IS setup!")));

        FWeaponDefinition* FoundWeaponDefinition = WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(WeaponDefinitionRowHandle.RowName, "");
        
        FWeaponFunctionDefinition FoundWeaponFunctionDefinition = FoundWeaponDefinition->PrimaryWeaponFunctionDefinition;
        
        if(WeaponFunction == EWeaponFunction::Secondary)
        {
            FoundWeaponFunctionDefinition = FoundWeaponDefinition->SecondaryWeaponFunctionDefinition;
        }
        
        CurrentWeaponFunction = WeaponFunction;
        
        bool Handled = false;
        // OnCustomStartShooting(*FoundWeaponDefinition, FoundWeaponFunctionDefinition, WeaponFunction, Handled);
        
        if(!Handled)
        {
            if(IsReloading)
            {
                if(!IsShooting)
                {
                    IsShooting = true;
                }
                return;
            }
            
//            CurrentWeaponFunction = WeaponFunction;
            
            uint32 Tock = TimerUtil->Tock();
            
            float CurrCadence = FoundWeaponFunctionDefinition.Cadence;
            
            if(!IsShooting){
                if(Tock == 0)
                {
                    IsShooting = true;
                    TimerUtil->Tick();

                    GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UWeaponSysWeaponBase::FireShot, CurrCadence, true, 0.0f);
                    return;
                }
            }

            uint32 TockDiv = TimerUtil->TockDiv(Tock);
            
            if(!IsShooting && (Tock == 0 || TockDiv >= CurrCadence))
            {
                IsShooting = true;
                TimerUtil->Tick();

                GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UWeaponSysWeaponBase::FireShot, CurrCadence, true, 0.0f);
                if(Tock == 0){
                    FireShot();
                }
            }else if(!IsShooting && TockDiv < CurrCadence){
                IsShooting = true;
                GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UWeaponSysWeaponBase::FireShot, CurrCadence, true, CurrCadence - TockDiv);
            }
        }
        else
        {
            UDbg::DbgMsg(FString::Printf(TEXT("OnCustomStartShooting WAS Handled: %s"), *FoundWeaponDefinition->WeaponName));
        }
    }
}

void UWeaponSysWeaponBase::StopShooting()
{
    if(WeaponDefinitionRowHandle.IsNull())
    {
        UDbg::DbgMsg(FString::Printf(TEXT("NO WeaponDefinition SetUp!")));
    }
    else
    {
//        UDbg::DbgMsg(FString::Printf(TEXT("UBaseWeaponComponent STOP SHOOTING!")));
        FWeaponDefinition* FoundWeaponDefinition = WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(WeaponDefinitionRowHandle.RowName, "");
        
        FWeaponFunctionDefinition FoundWeaponFunctionDefinition = FoundWeaponDefinition->PrimaryWeaponFunctionDefinition;
        
        if(CurrentWeaponFunction == EWeaponFunction::Secondary)
        {
            FoundWeaponFunctionDefinition = FoundWeaponDefinition->SecondaryWeaponFunctionDefinition;
        }
        
        bool Handled = false;
        // OnCustomStopShooting(*FoundWeaponDefinition, FoundWeaponFunctionDefinition, CurrentWeaponFunction, Handled);
        
        if(!Handled)
        {
            if(IsShooting)
            {
                IsShooting = false;
                GetWorld()->GetTimerManager().ClearTimer(ShootingTimerHandle);
            }

//            if(ShotAudioComponent)
//            {
//                UDbg::DbgMsg(FString("ShotAudioComponent->Stop();"));
//                ShotAudioComponent->Stop();
//                ShotAudioComponent = nullptr;
//            }
        }
    }
}

void UWeaponSysWeaponBase::FireShot()
{
    if(IsReloading)
    {
        return;
    }
    
    FWeaponDefinition* FoundWeaponDefinition = this->WeaponDefinition();//WeaponDefinitionRowHandle.DataTable->FindRow<FWeaponDefinition>(WeaponDefinitionRowHandle.RowName, "");
    
    //CurrentWeaponDefinition = FoundWeaponDefinition;
    
    FWeaponFunctionDefinition WeaponFunctionDefinition = FoundWeaponDefinition->PrimaryWeaponFunctionDefinition;
    
    if(CurrentWeaponFunction == EWeaponFunction::Secondary)
    {
        WeaponFunctionDefinition = FoundWeaponDefinition->SecondaryWeaponFunctionDefinition;
    }
    
    if(AmmoCount > 0 || AmmoCount == -1)
    {
        TSubclassOf<AWeaponSystemProjectile> ProjectileClass = WeaponFunctionDefinition.Projectile;
        if (ProjectileClass)
        {
            
            AActor* ActorRef = GetOwner();// GetWorld()->GetFirstPlayerController()->GetPawn();
            FVector CameraLocation;
            FRotator CameraRotation;
            ActorRef->GetActorEyesViewPoint(CameraLocation, CameraRotation);

            // FVector MuzzleOffset;
            // Set MuzzleOffset to spawn projectiles slightly in front of the camera.
            MuzzleOffset.Set(60.0f, 0.0f, 0.0f);
            FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
            FRotator MuzzleRotation = CameraRotation;

            UWorld* World = GetWorld();
            if (World)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = ActorRef;
                SpawnParams.Instigator = ActorRef->GetInstigator();

                // AWeaponSystemProjectile* Projectile = World->SpawnActor<AWeaponSystemProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
                // if (Projectile)
                // {
                //     FVector LaunchDirection = MuzzleRotation.Vector();
                //     Projectile->DamageFactor = WeaponFunctionDefinition.DamageFactor;
                //     // Projectile->WeaponFunctionDefinition = WeaponFunctionDefinition;
                //     Projectile->FireInDirection(LaunchDirection);

                //     // // OnShotFiredDelegate.Broadcast(*FoundWeaponDefinition, WeaponFunctionDefinition, CurrentWeaponFunction);
                //     // // OnProjectileFired.Broadcast(Projectile);

                //     // if(ShotAudioComponent)
                //     // {
                //     //     ShotAudioComponent->Stop();
                //     //     ShotAudioComponent = nullptr;
                //     // }

                //     // ShotAudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, WeaponFunctionDefinition.ShootingSound, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FRotator::ZeroRotator, 1.0, 1.0, 0.0f, nullptr, nullptr, true);
                    
                //     // if(AmmoCount > 0)
                //     // {
                //     //     AmmoCount--;
                //     // }
                    
                //     // AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
                //     // if(AmmoCount > -1)
                //     // {
                //     //     if(AmmoCount > 0 && (AmmoCount % FoundWeaponDefinition->ClipSize) == 0)
                //     //     {
                //     //         IsReloading = true;
                //     //         // UDbg::DbgMsg(FString::Printf(TEXT("RELOADING!!!!!!")));
                //     //         GetWorld()->GetTimerManager().SetTimer(ReloadingStartTimerHandle, this, &UBaseWeaponComponent::StartReloading, 0.01f, true, 0.01f);
                //     //         this->OnWeaponReloading.Broadcast(FoundWeaponDefinition->ReloadTimeout);
                //     //         // AWeaponSystemHUD* WeaponSystemHUD = Cast<AWeaponSystemHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
                //     //         if(this->GetOwner() == GetWorld()->GetFirstPlayerController()->GetPawn())
                //     //         {
                //     //             if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget)
                //     //             {
                //     //                 WeaponSystemHUD->InfoHUDWidget->OnShowReloadProgressBar(WeaponDefinition()->ReloadTimeout);
                //     //             }
                //     //             else
                //     //             {
                //     //                 UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD IS NULL")));
                //     //             }
                //     //         }
                //     //     }
                //     // }

                //     // if(WeaponSystemHUD && WeaponSystemHUD->InfoHUDWidget && (this->GetOwner() == GetWorld()->GetFirstPlayerController()->GetPawn()))
                //     // {
                //     //     if(!IsReloading)
                //     //     {
                //     //         WeaponSystemHUD->InfoHUDWidget->OnShowReloadProgressBar(WeaponFunctionDefinition.Cadence);
                //     //     }
                //     //     WeaponSystemHUD->InfoHUDWidget->AmmoCount = AmmoCount;
                //     //     WeaponSystemHUD->InfoHUDWidget->ClipAmmoCount = GetClipAmmoCount();// (AmmoCount %  WeaponDefinition()->ClipSize);// ClipAmmoCount;
                //     // }
                //     // else
                //     // {
                //     //     UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD IS NULL")));
                //     // }
                // }
            }
        }
    }
    else
    {
        if(FoundWeaponDefinition->MagEmptySound)
        {
            UDbg::DbgMsg(FString::Printf(TEXT("Playing MagEmptySound!")));
            UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, FoundWeaponDefinition->MagEmptySound, GetOwner()->GetActorLocation(), FRotator::ZeroRotator, 2.0, 1.0, 0.0f, nullptr, nullptr, true);
        }
    }
}