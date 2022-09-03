//
//  WeaponSysHUDInfoWidget.h
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
// #include "Components/WidgetComponent.h"
// #include "Utils/HUDFunc.h"
// #include "Utils/Dbg.h"
#include "WeaponSysHUDInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSBASEPLUGIN_API UWeaponSysHUDInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
    
public:

    // /** Property replication */
	// void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 Score = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 AmmoCountClip = 30;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    int32 AmmoCountTotal = 30;

    UFUNCTION(BlueprintCallable, Category="Weapon System|HUD")
    void ShowInfoMessage(const FString& Title, const FString& Desc);

    // UFUNCTION(BlueprintCallable, Category="Weapon System|HUD")
    // void ShowReloadProgressBar(float ReloadTime);

    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System|HUD")
    void OnShowInfoMessage(const FString& Title, const FString& Desc);

    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System|HUD")
    void OnShowReloadProgressBar(float ReloadTime);

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
