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
FSClient *swkbdCli = NULL;

uint32_t Swkbd_GetWorkMemorySize(uint32_t unk)
{
	return nn::swkbd::GetWorkMemorySize(unk);
}

bool Swkbd_AppearInputForm()
{
	nn::swkbd::AppearArg appearArg;
	
	OSBlockSet(&appearArg.keyboardArg.configArg, 0, sizeof(nn::swkbd::AppearArg));
	
	appearArg.keyboardArg.configArg.languageType = nn::swkbd::LanguageType::English;
	appearArg.keyboardArg.configArg.unk_0x04 = 4;
	appearArg.keyboardArg.configArg.unk_0x08 = 0;
	appearArg.keyboardArg.configArg.unk_0x0C = 0x7FFFF;
	appearArg.keyboardArg.configArg.unk_0x10 = 19;
	appearArg.keyboardArg.configArg.unk_0x14 = -1;
	appearArg.keyboardArg.configArg.unk_0x9C = 1;
	appearArg.keyboardArg.configArg.unk_0xA4 = -1;
	
	appearArg.keyboardArg.receiverArg.unk_0x00 = 0;
	appearArg.keyboardArg.receiverArg.unk_0x04 = 0;
	appearArg.keyboardArg.receiverArg.unk_0x08 = 0;
	appearArg.keyboardArg.receiverArg.unk_0x0C = 0;
	appearArg.keyboardArg.receiverArg.unk_0x10 = 0;
	appearArg.keyboardArg.receiverArg.unk_0x14 = 2;
	
	appearArg.inputFormArg.unk_0x00 = 1;
	appearArg.inputFormArg.unk_0x04 = -1;
	appearArg.inputFormArg.unk_0x08 = (uint32_t)nullptr;
	appearArg.inputFormArg.unk_0x0C = (uint32_t)nullptr;
	appearArg.inputFormArg.unk_0x14 = 0;
	appearArg.inputFormArg.unk_0x18 = 0x00008000;
	appearArg.inputFormArg.unk_0x1C = true;
	appearArg.inputFormArg.unk_0x1D = true;
	appearArg.inputFormArg.unk_0x1E = true;
	appearArg.inputFormArg.maxTextLength = -1;
	return nn::swkbd::AppearInputForm(appearArg);
}

bool Swkbd_Create()
{
	swkbdCli = (FSClient *)MEMAllocFromDefaultHeap(sizeof(FSClient));
	createArg.workMemory = MEMAllocFromDefaultHeap(Swkbd_GetWorkMemorySize(0));
	if(swkbdCli == NULL || createArg.workMemory == NULL)
	{
		WHBLogPrintf("SWKBD: Can't allocate memory!");
		return false;
	}
	
	FSAddClient(swkbdCli, 0);
	
	createArg.regionType = nn::swkbd::RegionType::Europe;
	createArg.unk_0x08 = 0;
	createArg.fsClient = swkbdCli;
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
	
	if(swkbdCli != NULL)
	{
		FSDelClient(swkbdCli, 0);
		MEMFreeToDefaultHeap(swkbdCli);
		swkbdCli = NULL;
	}
}
