// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Weapon/WeaponSysWeaponManager.h"

// Sets default values for this component's properties
UWeaponSysWeaponManager::UWeaponSysWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponSysWeaponManager::BeginPlay()
{
	Super::BeginPlay();
   
    int32 idx = 0;
    for(TSubclassOf<UWeaponSysWeaponBase> Weapon: WeaponArsenal)
    {
        UWeaponSysWeaponBase* NewWeapon = Cast<UWeaponSysWeaponBase>(Weapon->GetDefaultObject());
        
        UWeaponSysWeaponBase* NewWeaponImpl = NewObject<UWeaponSysWeaponBase>(this, NewWeapon->GetClass(), *NewWeapon->GetClass()->GetName());

        // NewWeaponImpl->MuzzleOffset = MuzzleOffset;
        // NewWeaponImpl->OnShotFiredDelegate.AddDynamic(this, &UWeaponSysWeaponManager::OnShotFired);        
        // NewWeaponImpl->OnWeaponReloading.AddDynamic(this, &UWeaponSysWeaponManager::WeaponReloading);

//        NewWeaponImpl->OnProjectileFireDelegate.AddDynamic(this, &UWeaponManagerComponentBase::ProjectileFired);
//        NewWeaponImpl->OnProjectileHitDelegate.AddDynamic(this, &UWeaponManagerComponentBase::ProjectileHit);

        NewWeaponImpl->RegisterComponent();
        WeaponArsenalImpl.AddUnique(NewWeaponImpl);
        // if(idx == 0)
        // {
        //     SetCurrentWeapon(NewWeaponImpl->WeaponDefinition()->WeaponID);
        // }
        idx++;
    }
    
    // this->SetComponentTickInterval(0.05f);
}


// Called every frame
void UWeaponSysWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

