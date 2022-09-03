//
//  ScoreHelper.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScoreHelper.generated.h"

UCLASS()
class UEWEAPONSYSBASEPLUGIN_API UScoreHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"), Category="Score")
    static void SpawnMovingScoreWidget(UObject* WorldContextObject, const float Score, FVector Location, FRotator Rotation);

};
