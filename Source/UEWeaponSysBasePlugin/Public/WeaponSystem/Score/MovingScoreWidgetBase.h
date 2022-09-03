//
//  MovingScoreWidgetBase.h
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 31.03.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "MovingScoreWidgetBase.generated.h"

UCLASS()
class UEWEAPONSYSBASEPLUGIN_API UMovingScoreWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;
    
public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Score System")
    float Score = 200.0f;
    
    UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category="Score System", meta=(BindWidgetAnim))
    UWidgetAnimation* MoveUpAndFadeOutAnim;
    
    UFUNCTION(BlueprintCallable, Category="Score System")
    void PlayMoveAndFadeAnim();
    
};
