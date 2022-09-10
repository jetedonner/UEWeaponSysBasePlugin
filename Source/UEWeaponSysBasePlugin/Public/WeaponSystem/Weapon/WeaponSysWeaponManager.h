//
//  WeaponSysWeaponManager.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSysWeaponBase.h"
#include "WeaponSysWeaponManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEWEAPONSYSBASEPLUGIN_API UWeaponSysWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponSysWeaponManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System", meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"))
    UDataTable* WeaponDefinitions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<TSubclassOf<class UWeaponSysWeaponBase>> WeaponArsenal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<class UWeaponSysWeaponBase*> WeaponArsenalImpl;

	UFUNCTION(BlueprintCallable, Category="Weapon System")
    void PickupWeapon(int32 WeaponID, int32 AmmoCount);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon System")
    class UWeaponSysWeaponBase* CurrentWeapon;

	UFUNCTION(BlueprintCallable, Category="Weapon System")
    void SetCurrentWeapon(int32 WeaponID, bool PlayAudio = true);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
