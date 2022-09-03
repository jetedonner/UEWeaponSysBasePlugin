//
//  HitableSphereActorBase.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "Hitables/HitableSphereActorBase.h"

// Sets default values
AHitableSphereActorBase::AHitableSphereActorBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

AHitableSphereActorBase::AHitableSphereActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    
    if(!CollisionComponent)
    {
        CollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereCollision"));
        Cast<USphereComponent>(CollisionComponent)->SetSphereRadius(100.0f, true);
        CollisionComponent->bEditableWhenInherited = true;
        CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
        RootComponent = CollisionComponent;
        AttachMesh();
    }
}
