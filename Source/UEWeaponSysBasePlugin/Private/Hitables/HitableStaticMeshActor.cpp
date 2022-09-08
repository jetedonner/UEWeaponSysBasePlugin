//
//  HitableStaticMeshActor.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 05.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Hitables/HitableStaticMeshActor.h"

AHitableStaticMeshActor::AHitableStaticMeshActor():Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHitableStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();

    if(AttachOnHitToStaticMesh)
    {
        Cast<UStaticMeshComponent>(RootComponent)->OnComponentHit.AddDynamic(this, &AHitableStaticMeshActor::OnHit);
    }
}

void AHitableStaticMeshActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{   
    if(Cast<AWeaponSysBaseProjectile>(OtherActor))
    {
        if(AllowMultipleHits || !IsHit)
        {
            IsHit = true;

            if(HitScore > 0.f || HitScore < 0.f)
            {
                AWeaponSysBaseCharacter* WeaponSysCharacter = Cast<AWeaponSysBaseCharacter>(OtherActor->GetInstigator());
                if(WeaponSysCharacter && WeaponSysCharacter->ScoreManagerComponent)
                {
                    WeaponSysCharacter->ScoreManagerComponent->AddScore(HitScore);
                }

                if(ShowHitScore)
                {
                    UScoreHelper::SpawnMovingScoreWidget(GetWorld(), HitScore, GetActorLocation(), GetActorRotation());
                }
            }
        }
    }
}