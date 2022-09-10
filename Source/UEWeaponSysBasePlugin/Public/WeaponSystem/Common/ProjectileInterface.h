// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectileInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProjectileInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UEWEAPONSYSBASEPLUGIN_API IProjectileInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter=GetDamageFactor, BlueprintSetter=SetDamageFactor, Category="Weapon System")
    // float DamageFactor;

	// UFUNCTION(BlueprintCallable, Category="Weapon System")
	// virtual float GetDamageFactor(){ return 5.0f };

	// UFUNCTION(BlueprintCallable, Category="Weapon System")
	// virtual void SetDamageFactor(float NewDamageFact){  };


};
