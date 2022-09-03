// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<TSubclassOf<class UWeaponSysWeaponBase>> WeaponArsenal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<class UWeaponSysWeaponBase*> WeaponArsenalImpl;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
