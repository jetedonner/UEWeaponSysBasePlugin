//
//  FloatingHealthBarWidgetComponent.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 02.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FloatingHealthBarWidgetComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEWEAPONSYSBASEPLUGIN_API UFloatingHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UFloatingHealthBarWidgetComponent();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// /** Response to health being updated. Called on the server immediately after modification, and on clients in response to a RepNotify*/
	// void OnHealthUpdate();

	// /** RepNotify for changes made to current health.*/
	// UFUNCTION()
	// void OnRep_CurrentHealth();

public:	
	
	// UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	// float CurrentHealth;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
