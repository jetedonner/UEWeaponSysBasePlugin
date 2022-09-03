//
//  MovingScoreWidgetBase.cpp
//  UEWeaponSystemPlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Score/MovingScoreWidgetBase.h"

void UMovingScoreWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();
}

void UMovingScoreWidgetBase::PlayMoveAndFadeAnim()
{
    if(MoveUpAndFadeOutAnim)
    {
        PlayAnimation(MoveUpAndFadeOutAnim, 0.0f, 1.0f, EUMGSequencePlayMode::Forward, 1.0f, false);
    }
    else
    {
        UDbg::DbgMsg(FString::Printf(TEXT("UMovingScoreWidgetBase NO ANIMATION SET!")));
    }
}