//
//  HitableInterface.cpp
//  UE4 WeaponSystem Plugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "WeaponSystem/Common/HitableInterface.h"

bool IHitableInterface::HasHitScore()
{
    return false;
}

int32 IHitableInterface::HitScore()
{
    return 100;
}