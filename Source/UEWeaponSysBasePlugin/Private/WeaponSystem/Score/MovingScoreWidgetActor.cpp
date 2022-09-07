//
//  MovingScoreWidgetActor.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Score/MovingScoreWidgetActor.h"

AMovingScoreWidgetActor::AMovingScoreWidgetActor()
{
	PrimaryActorTick.bCanEverTick = true;

    if(!MovingScoreWidgetComponent)
    {
        MovingScoreWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("MovingScoreWidget Component"));
        
        static ConstructorHelpers::FClassFinder<UUserWidget> MovingScoreWidget(TEXT("/UEWeaponSysBasePlugin/Widgets/MovingScoreWidget"));
        
        MovingScoreWidgetClass = MovingScoreWidget.Class;

        MovingScoreWidgetComponent->bEditableWhenInherited = true;
        MovingScoreWidgetComponent->SetWidgetClass(MovingScoreWidget.Class);
        MovingScoreWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
        MovingScoreWidgetComponent->SetTwoSided(true);
        MovingScoreWidgetComponent->SetAbsolute(false, false, true);
        MovingScoreWidgetComponent->SetRelativeLocation(FVector(0, 0, 150 + 20));
        MovingScoreWidgetComponent->SetCollisionProfileName(TEXT("UI"));
        // MovingScoreWidgetComponent->SetupAttachment(RootComponent);
        RootComponent = MovingScoreWidgetComponent;
    }
}

void AMovingScoreWidgetActor::BeginPlay()
{
	Super::BeginPlay();
    
    MovingScoreWidgetBase = Cast<UMovingScoreWidgetBase>(MovingScoreWidgetComponent->GetUserWidgetObject());
    MovingScoreWidgetBase->Score = Score;
    
    StartDelegate.BindDynamic(this, &AMovingScoreWidgetActor::AnimationStarted);
    EndDelegate.BindDynamic(this, &AMovingScoreWidgetActor::AnimationFinished);

    MovingScoreWidgetBase->BindToAnimationStarted(MovingScoreWidgetBase->MoveUpAndFadeOutAnim, StartDelegate);
    MovingScoreWidgetBase->BindToAnimationFinished(MovingScoreWidgetBase->MoveUpAndFadeOutAnim, EndDelegate);
    
    
    FTransform LocalToWorld;
    FBoxSphereBounds BoxSphereBounds = MovingScoreWidgetComponent->CalcBounds(LocalToWorld);
    
    if(MovingScoreWidgetBase)
    {
        MovingScoreWidgetBase->PlayMoveAndFadeAnim();
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("AMovingScoreWidgetActor::BeginPlay NO MovingScoreWidgetBase SET!")));
    }
}

void AMovingScoreWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMovingScoreWidgetActor::AnimationStarted()
{
    // some thing goes on here
}

void AMovingScoreWidgetActor::AnimationFinished()
{
//    UDbg::DbgMsg(FString::Printf(TEXT("AMovingScoreWidgetActor::AnimationFinished()!")));
    Destroy();
}
