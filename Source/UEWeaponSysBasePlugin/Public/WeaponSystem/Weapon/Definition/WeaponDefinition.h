//
//  WeaponDefinition.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "InputCoreTypes.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"
#include "WeaponSystem/Weapon/Definition/WeaponFunctionDefinition.h"
#include "Blueprint/UserWidget.h"
#include "WeaponDefinition.generated.h"

USTRUCT(Blueprintable)
struct FWeaponDefinition : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
    
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 WeaponID = -1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FString WeaponName = "BaseWeaponDefinition";
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FString WeaponDescription = "BaseWeaponDescription";
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 ClipSize = 30;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 PickUpCount = 30;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    float ReloadTimeout = 1.0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FKey ActivationKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* MagEmptySound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    USoundCue* ReloadSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    UTexture2D* HUDIcon;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    UTexture2D* InfoHUDIcon;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FWeaponFunctionDefinition PrimaryWeaponFunctionDefinition = FWeaponFunctionDefinition(EWeaponFunction::Primary);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    bool HasSecondaryFunction = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System", meta=(EditCondition="HasSecondaryFunction"))
    FWeaponFunctionDefinition SecondaryWeaponFunctionDefinition = FWeaponFunctionDefinition(EWeaponFunction::Secondary);

};
