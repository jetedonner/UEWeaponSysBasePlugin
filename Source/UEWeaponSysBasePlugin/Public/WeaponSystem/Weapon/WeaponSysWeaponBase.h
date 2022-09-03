// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponSystem/Weapon/Definition/WeaponDefinition.h"
#include "WeaponSysWeaponBase.generated.h"

UCLASS()
class UEWEAPONSYSBASEPLUGIN_API UWeaponSysWeaponBase : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UWeaponSysWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsTest = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsShooting = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool IsReloading = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"), Category="Weapon System")
    FDataTableRowHandle WeaponDefinitionRowHandle;
    
    // FWeaponDefinition* WeaponDefinition();
    
    EWeaponFunction CurrentWeaponFunction = EWeaponFunction::Primary;

	// // Called every frame
	// virtual void Tick(float DeltaTime) override;
	
};
