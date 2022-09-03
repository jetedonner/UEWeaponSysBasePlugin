// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Character/WeaponSysBasePlayerController.h"

void AWeaponSysBasePlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    UDbg::DbgMsg(FString::Printf(TEXT("AWeaponSysBasePlayerController::OnPossess(InPawn)!")), 5.0f, FColor::Red);
}