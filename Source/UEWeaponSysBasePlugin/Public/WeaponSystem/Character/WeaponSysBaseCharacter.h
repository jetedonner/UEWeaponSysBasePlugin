// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponSystem/Health/HealthManagerComponent.h"
#include "WeaponSystem/Weapon/WeaponSysWeaponManager.h"
#include "WeaponSystem/Score/ScoreManagerComponent.h"
#include "WeaponSystem/Common/HitableInterface.h"
#include "WeaponSysBaseCharacter.generated.h"

UCLASS(config=Game)
class AWeaponSysBaseCharacter : public ACharacter, public IHitableInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AWeaponSysBaseCharacter();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
    class UWeaponSysWeaponManager* WeaponManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health System")
    class UHealthManagerComponent* HealthManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score System")
    class UScoreManagerComponent* ScoreManagerComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// /** Getter for Max Health.*/
	// UFUNCTION(BlueprintPure, Category="Health")
	// FORCEINLINE float GetMaxHealth() const { return MaxHealth; } 

	// /** Getter for Current Health.*/
	// UFUNCTION(BlueprintPure, Category="Health")
	// FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	// /** Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.*/
	// UFUNCTION(BlueprintCallable, Category="Health")
	// void SetCurrentHealth(float healthValue);

	/** Event for taking damage. Overridden from APawn.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage( float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;

protected:

	/** The player's maximum health. This is the highest that their health can be, and the value that their health starts at when spawned.*/
	// UPROPERTY(EditDefaultsOnly, Category = "Health")
	// float MaxHealth;

	// /** The player's current health. When reduced to 0, they are considered dead.*/
	// UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	// float CurrentHealth;

	// /** Response to health being updated. Called on the server immediately after modification, and on clients in response to a RepNotify*/
	// void OnHealthUpdate();

	// /** RepNotify for changes made to current health.*/
	// UFUNCTION()
	// void OnRep_CurrentHealth();

	UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
	TSubclassOf<class AWeaponSysBaseProjectile> ProjectileClass;

	/** Delay between shots in seconds. Used to control fire rate for our test projectile, but also to prevent an overflow of server functions from binding SpawnProjectile directly to input.*/
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;

	/** If true, we are in the process of firing projectiles. */
	bool bIsFiringWeapon;

	/** Function for beginning weapon fire.*/
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void StartFire();

	/** Function for ending weapon fire. Once this is called, the player can use StartFire again.*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopFire();  

	/** Server function for spawning projectiles.*/
	UFUNCTION(Server, Reliable)
	void HandleFire();

	/** A timer handle used for providing the fire rate delay in-between spawns.*/
	FTimerHandle FiringTimer;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon System")
	// FORCEINLINE bool HasHitScore() const { return true; }

	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon System")
	// FORCEINLINE int32 HitScore() const { return 200; }

	// UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon System")
  	// bool HasHitScore(); virtual bool HasHitScore_Implementation() override;

	virtual bool HasHitScore() override;

	virtual int32 HitScore() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon System")
	int32 InitHitScore = 100;
};

