//
//  HitableInterface.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//


#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HitableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UHitableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UEWEAPONSYSBASEPLUGIN_API IHitableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// UFUNCTION(BlueprintCallable, Category="Score System")
	virtual bool HasHitScore();

	// UFUNCTION(BlueprintCallable, Category="Score System")
	virtual int32 GetHitScore();
};
