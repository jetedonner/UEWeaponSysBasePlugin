// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeaponSystem/Character/WeaponSysBaseCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "WeaponSystem/Projectile/WeaponSysBaseProjectile.h"

//////////////////////////////////////////////////////////////////////////
// AWeaponSysBaseCharacter

AWeaponSysBaseCharacter::AWeaponSysBaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(50.f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	//Initialize the player's Health
	// MaxHealth = 100.0f;
	// CurrentHealth = MaxHealth;

	//Initialize projectile class
	ProjectileClass = AWeaponSysBaseProjectile::StaticClass();
	//Initialize fire rate
	FireRate = 0.25f;
	bIsFiringWeapon = false;

	if(!HealthManagerComponent)
    {
        HealthManagerComponent = CreateDefaultSubobject<UHealthManagerComponent>(TEXT("Health Manager Component"));
		if(HealthManagerComponent)
    	{
			HealthManagerComponent->bEditableWhenInherited = true;
			HealthManagerComponent->SetNetAddressable(); // Make DSO components net addressable
			HealthManagerComponent->SetIsReplicated(true);
			this->AddOwnedComponent(HealthManagerComponent);
			// HealthManagerComponent->SetupAttachment(RootComponent);
		}
    }

	if(!ScoreManagerComponent)
    {
        ScoreManagerComponent = CreateDefaultSubobject<UScoreManagerComponent>(TEXT("Score Manager Component"));
		if(ScoreManagerComponent)
    	{
			ScoreManagerComponent->bEditableWhenInherited = true;
			ScoreManagerComponent->SetNetAddressable(); // Make DSO components net addressable
			ScoreManagerComponent->SetIsReplicated(true);
			this->AddOwnedComponent(ScoreManagerComponent);
			// HealthManagerComponent->SetupAttachment(RootComponent);
		}
    }

	if(!WeaponManagerComponent)
    {
        WeaponManagerComponent = CreateDefaultSubobject<UWeaponSysWeaponManager>(TEXT("Weapon Manager Component"));
        WeaponManagerComponent->bEditableWhenInherited = true;
        this->AddOwnedComponent(WeaponManagerComponent);
    }
}

//////////////////////////////////////////////////////////////////////////
// Replicated Properties

void AWeaponSysBaseCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //Replicate current health.
    // DOREPLIFETIME(AWeaponSysBaseCharacter, CurrentHealth);
}

// void AWeaponSysBaseCharacter::OnHealthUpdate()
// {
//     //Client-specific functionality
//     if (IsLocallyControlled())
//     {
//         FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
//         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

//         if (CurrentHealth <= 0)
//         {
//             FString deathMessage = FString::Printf(TEXT("You have been killed."));
//             GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
//         }
//     }

//     //Server-specific functionality
//     if (GetLocalRole() == ROLE_Authority)
//     {
//         FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
//         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
//     }

//     //Functions that occur on all machines. 
//     /*  
//         Any special functionality that should occur as a result of damage or death should be placed here. 
//     */
// }

// void AWeaponSysBaseCharacter::OnRep_CurrentHealth()
// {
//     OnHealthUpdate();
// }

// void AWeaponSysBaseCharacter::SetCurrentHealth(float healthValue)
// {
//     if (GetLocalRole() == ROLE_Authority)
//     {
//         CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
//         OnHealthUpdate();
//     }
// }

float AWeaponSysBaseCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(this->HasHitScore() && (this->GetHitScore() > 0.f || this->GetHitScore() < 0.f))
	{
		// UDbg::DbgMsg(FString::Printf(TEXT("Score earned %d"), this->HitScore()), 5.0f, FColor::Purple);
		UScoreHelper::SpawnMovingScoreWidget(GetWorld(), this->GetHitScore(), GetActorLocation(), GetActorRotation());
	}

	return HealthManagerComponent->ApplyDamage(DamageTaken);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWeaponSysBaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWeaponSysBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWeaponSysBaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AWeaponSysBaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AWeaponSysBaseCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AWeaponSysBaseCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AWeaponSysBaseCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AWeaponSysBaseCharacter::OnResetVR);

	// Handle firing projectiles
	// PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AWeaponSysBaseCharacter::StartFire);

	FInputKeyBinding KBP_FPVKey(FInputChord(FPVKey, false, false, false, false), EInputEvent::IE_Pressed);
    KBP_FPVKey.bConsumeInput = true;
    KBP_FPVKey.bExecuteWhenPaused = false;

    KBP_FPVKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    {
        ToggleFPV();
    });
    PlayerInputComponent->KeyBindings.Add(KBP_FPVKey);

	if(WeaponManagerComponent)
	{
		WeaponManagerComponent->SetupPlayerInput(PlayerInputComponent, InputComponent);
	}
    
    // FInputKeyBinding KBR_PrimaryShootKey(FInputChord(FPVKey, false, false, false, false), EInputEvent::IE_Released);
    // KBR_PrimaryShootKey.bConsumeInput = true;
    // KBR_PrimaryShootKey.bExecuteWhenPaused = false;
    // KBR_PrimaryShootKey.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
    // {
    //     StopShooting();
    // });
    // InputComponent->KeyBindings.Add(KBR_PrimaryShootKey);
	// FPVKey
}

void AWeaponSysBaseCharacter::ToggleFPV()
{
	FirstPersonView = !FirstPersonView;
	if(FirstPersonView)
	{
		//Activate 3rd person
		FollowCamera->Deactivate();
		FirstPersonCameraComponent->Activate();
	}
	else
	{
		//Activate 1st person
		FirstPersonCameraComponent->Deactivate();
		FollowCamera->Activate();
	}

	AWeaponSysHUDBase* WeaponSystemHUD = Cast<AWeaponSysHUDBase>(Cast<APlayerController>(Controller)->GetHUD());
	if(WeaponSystemHUD)
	{   
		// if(WeaponSystemHUD->CrosshairUserWidget)
		// {
		//     WeaponSystemHUD->CrosshairUserWidget->ShowCrosshair(WeaponID);
		// }

		if(WeaponSystemHUD->InfoHUDWidget)
		{
			// WeaponSystemHUD->InfoHUDWidget->WeaponDefinition = *CurrentWeapon->WeaponDefinition();
			// WeaponSystemHUD->InfoHUDWidget->AmmoCountTotal = CurrentWeapon->AmmoCount;
			// WeaponSystemHUD->InfoHUDWidget->AmmoCountClip = CurrentWeapon->GetClipAmmoCount();
			WeaponSystemHUD->InfoHUDWidget->FPV = FirstPersonView;
		}
		else
		{
			UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD->InfoHUDWidget IS NULL")), 5.0f, FColor::Green);
		}
	}
	else
	{
		UDbg::DbgMsg(FString::Printf(TEXT("WeaponSystemHUD IS NULL")), 5.0f, FColor::Green);
	}
}

void AWeaponSysBaseCharacter::OnResetVR()
{
	// If ThirdPersonMP is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in ThirdPersonMP.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AWeaponSysBaseCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AWeaponSysBaseCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AWeaponSysBaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AWeaponSysBaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AWeaponSysBaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AWeaponSysBaseCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AWeaponSysBaseCharacter::StartFire()
{
    if (!bIsFiringWeapon && WeaponManagerComponent && WeaponManagerComponent->CurrentWeapon)
    {
        bIsFiringWeapon = true;
        UWorld* World = GetWorld();
        World->GetTimerManager().SetTimer(FiringTimer, this, &AWeaponSysBaseCharacter::StopFire, FireRate, false);
        HandleFire();
    }
}

void AWeaponSysBaseCharacter::StopFire()
{
    bIsFiringWeapon = false;
}

void AWeaponSysBaseCharacter::HandleFire_Implementation()
{
    FVector spawnLocation = GetActorLocation() + ( GetControlRotation().Vector()  * 100.0f ) + (GetActorUpVector() * 50.0f);
    FRotator spawnRotation = GetControlRotation();

    FActorSpawnParameters spawnParameters;
    spawnParameters.Instigator = GetInstigator();
    spawnParameters.Owner = this;

    AWeaponSysBaseProjectile* spawnedProjectile = GetWorld()->SpawnActor<AWeaponSysBaseProjectile>(ProjectileClass, spawnLocation, spawnRotation, spawnParameters);
}

bool AWeaponSysBaseCharacter::HasHitScore()
{
    return true;
}

int32 AWeaponSysBaseCharacter::GetHitScore()
{
    return this->HitScore;
}