//
//  WeaponSysWeaponBase.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystem/Weapon/Definition/WeaponDefinition.h"
#include "Utils/UtilityTimer.h"
#include "WeaponSysWeaponBase.generated.h"

UCLASS()
class UEWEAPONSYSBASEPLUGIN_API UWeaponSysWeaponBase : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UWeaponSysWeaponBase();
    UWeaponSysWeaponBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

    FTimerHandle ReloadingEndTimerHandle;
    FTimerHandle ReloadingStartTimerHandle;
    
//    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    // FWeaponDefinition* CurrentWeaponDefinition;

    FTimerHandle ShootingTimerHandle;
    
    class UtilityTimer* TimerUtil = new UtilityTimer();

public:	
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    // bool IsTest = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    UAudioComponent* ShotAudioComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon System")
    FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsShooting = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsReloading = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"), Category="Weapon System")
    FDataTableRowHandle WeaponDefinitionRowHandle;
    
    // FWeaponDefinition* WeaponDefinition();
    
    EWeaponFunction CurrentWeaponFunction = EWeaponFunction::Primary;

	FWeaponDefinition* WeaponDefinition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System") //BlueprintGetter=GetAmmoCount, BlueprintSetter=SetAmmoCount, Category="Weapon System")
    int32 AmmoCount;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Weapon System")
    int32 GetClipAmmoCount()
    { 
        // UE_LOG(LogTemp, Warning, TEXT("GetClipAmmoCount() %d"), WeaponDefinition()->ClipSize);
        int32 ClipCount = AmmoCount % WeaponDefinition()->ClipSize;
        if(AmmoCount > 0)
        {
            if(ClipCount > 0)
            {
                return ClipCount;
            }
            else
            {
                return WeaponDefinition()->ClipSize;
            }
        }
        else
        {
            return AmmoCount;
        }
    }

	UFUNCTION(BlueprintCallable, Category="Weapon System")
    void StartShooting(EWeaponFunction WeaponFunction = EWeaponFunction::Primary);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void StopShooting();
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void FireShot();
    
    // UFUNCTION(BlueprintCallable, Category="Weapon System")
    // void StartReloading();
    
    // UFUNCTION(BlueprintCallable, Category="Weapon System")
    // void FinishReloading();

	// // Called every frame
	// virtual void Tick(float DeltaTime) override;
	
};
