//
//  FillCircleCrosshairUserWidget.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 22.08.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/HUD/Crosshair/DrawUserWidgetBase.h"
#include "FillCircleCrosshairUserWidget.generated.h"

UCLASS()
class UEWEAPONSYSBASEPLUGIN_API UFillCircleCrosshairUserWidget : public UDrawUserWidgetBase
{
	GENERATED_BODY()
    
protected:

    virtual void NativeConstruct() override;
    
    virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;
    
public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filled Circle Crosshair", Interp, meta = (BindWidget))
    float Radius = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filled Circle Crosshair", Interp, meta = (BindWidget))
    float InnerRadius = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filled Circle Crosshair", Interp, meta = (BindWidget))
    int InnerDistance = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filled Circle Crosshair", Interp, meta = (BindWidget))
    int NumSegments = 60;
    
};
