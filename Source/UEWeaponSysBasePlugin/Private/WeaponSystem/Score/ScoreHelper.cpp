//
//  ScoreHelper.cpp
//  UE4_WeaponSystemDemo
//
//  Created by Kim David Hauser on 24.03.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#include "WeaponSystem/Score/ScoreHelper.h"

void UScoreHelper::SpawnMovingScoreWidget(UObject* WorldContextObject, const float Score, FVector Location, FRotator Rotation)
{
    if(GEngine)
    {
        FVector PlayerLoc = GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        FRotator MovingScoreWidgetRot = UKismetMathLibrary::FindLookAtRotation(Location, PlayerLoc);
        FRotator MovingScoreWidgetRotNew = FRotator(0, MovingScoreWidgetRot.Yaw, 0);   
        AMovingScoreWidgetActor* MovingScoreWidgetActor = (AMovingScoreWidgetActor*) GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->SpawnActor<AMovingScoreWidgetActor>(AMovingScoreWidgetActor::StaticClass(), Location, MovingScoreWidgetRotNew);
        MovingScoreWidgetActor->MovingScoreWidgetBase->Score = Score;
    }
}
