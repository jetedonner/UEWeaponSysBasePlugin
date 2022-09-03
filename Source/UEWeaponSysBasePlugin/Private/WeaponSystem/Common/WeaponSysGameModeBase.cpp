// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Common/WeaponSysGameModeBase.h"

AWeaponSysGameModeBase::AWeaponSysGameModeBase():Super()
{
        //tell your custom game mode to use your custom player controller
	PlayerControllerClass = AWeaponSysBasePlayerController::StaticClass();

	//you can set whatever (if any) other default framework classes
    //you wish for this game mode as well
	// DefaultPawnClass = ACustomPawn::StaticClass();
	// GameStateClass = ACustomGameState::StaticClass();
	HUDClass = AWeaponSysHUDBase::StaticClass();
	// ReplaySpectatorPlayerControllerClass = ACustomReplaySpectatorPlayerController::StaticClass();
	// SpectatorClass = ACustomSpectatorClass::StaticClass();
}