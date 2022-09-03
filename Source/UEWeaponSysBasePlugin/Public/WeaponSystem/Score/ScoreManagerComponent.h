// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEWEAPONSYSBASEPLUGIN_API UScoreManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreManagerComponent();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing=OnRep_Score)
	int32 Score;

	/** Response to health being updated. Called on the server immediately after modification, and on clients in response to a RepNotify*/
	void OnScoreUpdate();

	/** RepNotify for changes made to current health.*/
	UFUNCTION()
	void OnRep_Score();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Score System")
	void SetScore(int32 Value);

	UFUNCTION(BlueprintCallable, Category="Score System")
	void AddScore(int32 Value);

	UFUNCTION(BlueprintCallable, Category="Score System")
	void ResetScore();

};
