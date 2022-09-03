//
//  WeaponSysHUDBase.cpp
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/HUD/WeaponSysHUDBase.h"

AWeaponSysHUDBase::AWeaponSysHUDBase() : Super()
{
//     static ConstructorHelpers::FClassFinder<UUserWidget> InfoHUDWidgetClass(TEXT("/UEWeaponSysBasePlugin/HUD/InfoHUDWidget.InfoHUDWidget_C"));

//     if (InfoHUDWidgetClass != NULL)
//     {
//         // InfoHUDWidgetRef = InfoHUDWidgetClass.Class;
//         UWeaponSysHUDInfoWidget* CreatedWidget = CreateWidget<UWeaponSysHUDInfoWidget>(GetWorld(), InfoHUDWidgetClass); 
//         InfoHUDWidget = CreatedWidget;//Cast<InfoHUDWidgetClass>(CreatedWidget);
// //         // InfoHUDWidgetRef* InfoWidget = Cast<InfoHUDWidgetRef>(CreatedWidget);
// //         // if(InfoHUDWidgetRef.Class InfoWidget = Cast<InfoHUDWidgetRef.Class>(CreatedWidget))
// //         // {
// //         //     InfoHUDWidget = InfoWidget;
// //         // }

//         //  UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass FOUND (ClassName: %s) ..."), *InfoHUDWidgetClass.Class->GetName());
//  //        DefaultPawnClass = PlayerPawnBPClass.Class;
//     }
//     else
//     {
//         UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass NOT FOUND ..."));
//     }
}

void AWeaponSysHUDBase::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // DOREPLIFETIME(UScoreManagerComponent, Score);
}

void AWeaponSysHUDBase::BeginPlay()
{
    Super::BeginPlay();

    // // If any widgets need to be added
    // if (AllUIWidgets.Num() > 0)
    // {
    //     // Iterate through all widgets
    //     for (TSubclassOf<UUserWidget> Widget : AllUIWidgets)
    //     {
            
    //         // Create an instance of the widget and add to viewport
    //         UUserWidget* CreatedWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
            
    //         if(CreatedWidget->GetClass() == InfoHUDWidgetRef)
    //         {
    //             // UDbg::DbgMsg(FString::Printf(TEXT("Found HUD INFO WIDGET!")));
    //             InfoHUDWidget = Cast<UHUDUserWidget>(CreatedWidget);
    //             // InfoHUDWidget->WeaponSystemCharacter = Cast<AWeaponSystemCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    //         }
            
    //         // UDbg::DbgMsg(FString::Printf(TEXT("Created Widget: %s!"), *CreatedWidget->GetClass()->GetName()));
            
    //         UCrosshairUserWidgetBase* CSWidget = Cast<UCrosshairUserWidgetBase>(CreatedWidget);
    //         if(CSWidget)
    //         {
    //             CrosshairUserWidget = CSWidget;
    //         }

    //         CreatedWidget->AddToViewport();

    //         // Store instanced widget in array
    //         CreatedWidgets.Add(CreatedWidget);
    //     }
    // }
//     if (InfoHUDWidgetClass != NULL)
//     {
//         // InfoHUDWidgetRef = InfoHUDWidgetClass.Class;
//         // UWeaponSysHUDInfoWidget* CreatedWidget 
//         InfoHUDWidget = CreateWidget<UWeaponSysHUDInfoWidget>(GetWorld(), InfoHUDWidgetClass); 
//         // InfoHUDWidget = CreatedWidget;//Cast<InfoHUDWidgetClass>(CreatedWidget);
//         UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass WAS FOUND ..."));
// //         // InfoHUDWidgetRef* InfoWidget = Cast<InfoHUDWidgetRef>(CreatedWidget);
// //         // if(InfoHUDWidgetRef.Class InfoWidget = Cast<InfoHUDWidgetRef.Class>(CreatedWidget))
// //         // {
// //         //     InfoHUDWidget = InfoWidget;
// //         // }

//         //  UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass FOUND (ClassName: %s) ..."), *InfoHUDWidgetClass.Class->GetName());
//  //        DefaultPawnClass = PlayerPawnBPClass.Class;
//     }
//     else
//     {
//         UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass NOT FOUND ..."));
//     }
    if (InfoHUDWidgetClass != NULL)
    {
        InfoHUDWidget = CreateWidget<UWeaponSysHUDInfoWidget>(this->GetOwningPlayerController(), InfoHUDWidgetClass); 
        UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass WAS FOUND ..."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("InfoHUDWidgetClass NOT FOUND ..."));
    }

    if(InfoHUDWidget)
    {
        InfoHUDWidget->AddToViewport();
        CreatedWidgets.Add(InfoHUDWidget);
    }
}

// void AWeaponSystemHUD::DrawHUD()
// {
//     Super::DrawHUD();
// }

// void AWeaponSystemHUD::ShowCrosshair(bool Show)
// {
//     if(CrosshairUserWidget)
//     {
//         if(Show)
//         {
//             CrosshairUserWidget->SetVisibility(ESlateVisibility::Visible);
//         }
//         else
//         {
//             CrosshairUserWidget->SetVisibility(ESlateVisibility::Hidden);
//         }
//     }
//     else
//     {
//         UDbg::DbgMsg(FString::Printf(TEXT("CrosshairUserWidget NOT SET!")));
//     }
// }

// void UWeaponSysHUDBase::NativeConstruct()
// {
//     Super::NativeConstruct();
// }

// void UWeaponSysHUDBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
// {
//     Super::NativeTick(MyGeometry, InDeltaTime);
// }

