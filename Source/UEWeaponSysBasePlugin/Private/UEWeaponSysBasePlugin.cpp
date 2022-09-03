//
//  UEWeaponSysBasePlugin.cpp
//  UEWeaponSysBasePlugin
//
//  Created by Kim David Hauser on 03.09.22.
//  Copyright © 1991 - 2022 DaVe Inc. kimhauser.ch, All rights reserved.
//

#include "UEWeaponSysBasePlugin.h"

#define LOCTEXT_NAMESPACE "FUEWeaponSysBasePluginModule"

DEFINE_LOG_CATEGORY(WeaponSysBasePlugin);

void FUEWeaponSysBasePluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUEWeaponSysBasePluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUEWeaponSysBasePluginModule, UEWeaponSysBasePlugin)