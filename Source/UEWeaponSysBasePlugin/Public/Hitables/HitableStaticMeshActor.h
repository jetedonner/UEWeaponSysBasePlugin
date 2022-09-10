//
//  HitableStaticMeshActor.h
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 05.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SphereComponent.h"
#include "WeaponSystem/Projectile/WeaponSysBaseProjectileBase.h"
#include "HitableStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class UEWEAPONSYSBASEPLUGIN_API AHitableStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
    
    AHitableStaticMeshActor();
    
protected:

    virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool AttachOnHitToStaticMesh = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool AllowMultipleHits = true;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool IsHit = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    bool ShowHitScore = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Event|Hit")
    float HitScore = 100.0f;

	UFUNCTION(BlueprintCallable, Category="Weapon System")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // UFUNCTION(BlueprintCallable, Category="Weapon System")
	// void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
