// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Weapon/WeaponSysWeaponBase.h"

// Sets default values
UWeaponSysWeaponBase::UWeaponSysWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UWeaponSysWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	// Some comment
	
}

// // Called every frame
// void AWeaponSysWeaponBase::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);

// }

