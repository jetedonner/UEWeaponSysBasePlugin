//
//  WeaponSysHUDWidgetBase.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSystem/HUD/Crosshair/DrawUserWidgetBase.h"
#include "WeaponSystem/HUD/Crosshair/CrosshairUserWidgetBase.h"
#include "WeaponSystem/HUD/WeaponSysHUDInfoWidget.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponSysHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSBASEPLUGIN_API AWeaponSysHUDBase : public AHUD
{
	GENERATED_BODY()

public:
    AWeaponSysHUDBase();

    /** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, Category="Weapon System")
    TArray<TSubclassOf<class UUserWidget>> AllUIWidgets;

// private: 
    TArray<class UUserWidget*> CreatedWidgets;
    
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    TSubclassOf<UWeaponSysHUDInfoWidget> InfoHUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System|HUD")
    UWeaponSysHUDInfoWidget* InfoHUDWidget;

    // /** Property replication */
	// void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    // float Health = 100.0f;

    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    // int32 Score = 0;

    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    // int32 AmmoCountClip = 30;

    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    // int32 AmmoCountTotal = 30;

    // UPROPERTY(ReplicatedUsing=OnRep_Health, EditAnywhere, BlueprintReadWrite, Category="Health System")
    // float Health = 100.0f;

    // // UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	// // float CurrentHealth;

	// /** Response to health being updated. Called on the server immediately after modification, and on clients in response to a RepNotify*/
	// void OnHealthUpdate();

	// /** RepNotify for changes made to current health.*/
	// UFUNCTION()
	// void OnRep_Health();

    // UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Health System")
    // class UWidgetComponent* ParentWidgetComponent;
};
