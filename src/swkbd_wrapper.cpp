/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#include <stdint.h>
#include <cstring>

#include <coreinit/filesystem.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memory.h>
#include <whb/log.h>

#include "swkbd_wrapper.h"

nn::swkbd::CreateArg createArg;

uint32_t Swkbd_GetWorkMemorySize(uint32_t unk)
{
	return nn::swkbd::GetWorkMemorySize(unk);
}

bool Swkbd_AppearInputForm()
{
	nn::swkbd::AppearArg appearArg;
	
	appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
	appearArg.inputFormArg.maxTextLength = -1;
	return nn::swkbd::AppearInputForm(appearArg);
}

bool Swkbd_Create()
{
	createArg.fsClient = (FSClient *)MEMAllocFromDefaultHeap(sizeof(FSClient));
	createArg.workMemory = MEMAllocFromDefaultHeap(Swkbd_GetWorkMemorySize(0));
	if(createArg.fsClient == NULL || createArg.workMemory == NULL)
	{
		WHBLogPrintf("SWKBD: Can't allocate memory!");
		return false;
	}
	
	FSAddClient(createArg.fsClient, 0);
	
	createArg.regionType = nn::swkbd::RegionType::Europe;
	return nn::swkbd::Create(createArg);
}

void Swkbd_SetEnableOkButton(bool enable)
{
	nn::swkbd::SetEnableOkButton(enable);
}

void Swkbd_Calc(VPADStatus vpad)
{
	nn::swkbd::ControllerInfo controllerInfo;
	controllerInfo.vpad = &vpad;
	controllerInfo.kpad[0] = nullptr;
	controllerInfo.kpad[1] = nullptr;
	controllerInfo.kpad[2] = nullptr;
	controllerInfo.kpad[3] = nullptr;
	nn::swkbd::Calc(controllerInfo);
}

bool Swkbd_IsNeedCalcSubThreadFont()
{
	return nn::swkbd::IsNeedCalcSubThreadFont();
}

void Swkbd_CalcSubThreadFont()
{
	nn::swkbd::CalcSubThreadFont();
}

void Swkbd_DrawTV()
{
	nn::swkbd::DrawTV();
}

void Swkbd_DrawDRC()
{
	nn::swkbd::DrawDRC();
}

bool Swkbd_DisappearInputForm()
{
	return nn::swkbd::DisappearInputForm();
}

void Swkbd_Destroy()
{
	nn::swkbd::Destroy();
	if(createArg.workMemory != NULL)
	{
		MEMFreeToDefaultHeap(createArg.workMemory);
		createArg.workMemory = NULL;
	}
	
	if(createArg.fsClient != NULL)
	{
		FSDelClient(createArg.fsClient, 0);
		MEMFreeToDefaultHeap(createArg.fsClient);
		createArg.fsClient = NULL;
	}
}
