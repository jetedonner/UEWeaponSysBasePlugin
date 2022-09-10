//
//  WeaponSystemProjectile.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 10.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "WeaponSystem/Weapon/Definition/DecalStruct.h"
#include "WeaponSystemProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FProjectileHitDelegate, AActor*, ProjectileActor, AActor*, OtherActor, FVector, Location);

UCLASS(Blueprintable)
class UEWEAPONSYSBASEPLUGIN_API AWeaponSystemProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponSystemProjectile();
    AWeaponSystemProjectile(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual void OutsideWorldBounds() override;
    
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RequiredAssetDataTags="RowStructure=WeaponDefinition"), Category="Weapon System")
    // FDataTableRowHandle WeaponDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    float DamageFactor = 5.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon System")
    bool DestroyOnHit = true;
    
    UFUNCTION()
    virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    UPROPERTY(BlueprintAssignable, Category="Weapon System")
    FProjectileHitDelegate OnProjectileHitDelegate;

    // Sphere collision component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
    USphereComponent* CollisionComponent;

    // Projectile movement component
    UPROPERTY(VisibleAnywhere, Category = Movement)
    UProjectileMovementComponent* ProjectileMovementComponent;

    // Projectile mesh
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UStaticMeshComponent* ProjectileMeshComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    FHitResult HitResult;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class UParticleSystem* ImpactEffect;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* ImpactTargetSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class USoundCue* ImpactFailSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    TArray<FDecalStruct> ImpactDecals;
    
    UPROPERTY(BlueprintReadOnly, Category="Weapon System")
    class UDecalComponent* ImpactDecalObject;

    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void SpawnRandomDecalAtLocation(FVector DecalLocation, FVector ImpactNormal, UPrimitiveComponent* OtherComponent);
    
    void FireInDirection(const FVector& ShootDirection);
    
    UFUNCTION(BlueprintCallable, Category="Weapon System")
    void LineTraceProjectile();
    
    UFUNCTION(BlueprintImplementableEvent, Category="Weapon System")
    void OnLineTraceHit(FHitResult LineTraceHitResult, bool HitCharacterOrHitable);

};
