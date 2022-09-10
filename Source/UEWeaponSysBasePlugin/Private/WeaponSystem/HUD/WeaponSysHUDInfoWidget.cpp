//
//  WeaponSysHUDInfoWidget.cpp
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/HUD/WeaponSysHUDInfoWidget.h"

void UWeaponSysHUDInfoWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UWeaponSysHUDInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if(IsReloading)
    {
        float ReloadingTimeElapsed = (float(TimerUtil->Tock())) / 10000000.0f;
        ReloadingProgress = ReloadingTimeElapsed / ReloadingDuration;
        
        // UDbg::DbgMsg(FString::Printf(TEXT("UWeaponSysHUDInfoWidget::NativeTick: %f / %f"), ReloadingTimeElapsed, InDeltaTime), 5.0f, FColor::Green);

        if(ReloadingProgress >= 1.0f)
        {
            IsReloading = false;
        }
    }
}

void UWeaponSysHUDInfoWidget::ShowReloadProgressBar(const float Duration)
{
    UDbg::DbgMsg(FString::Printf(TEXT("UWeaponSysHUDInfoWidget::ShowReloadProgressBar: %f"), Duration), 5.0f, FColor::Green);

    if(!IsReloading)
    {
        IsReloading = true;
        ReloadingDuration = Duration;
        TimerUtil->Tick();
    }
}

void UWeaponSysHUDInfoWidget::ShowInfoMessage(const FString& Title, const FString& Desc)
{
    // UDbg::DbgMsg(FString::Printf(TEXT("UWeaponSysHUDInfoWidget::ShowInfoMessage")), 5.0f, FColor::Green);
    this->OnShowInfoMessage(Title, Desc);
}