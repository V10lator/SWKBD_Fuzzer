/****************************************************************
 * This file is part of SWKBD_Fuzzer.                           *
 * (c) 2020 V10lator <v10lator@myway.de>                        *
 *                                                              *
 * Licensed under the MIT license (see LICENSE.txt for details) *
 ****************************************************************/

#include "guiWrapper.h"
#include "input.h"
#include "swkbd_wrapper.h"

#include <vpad/input.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memory.h>
#include <coreinit/thread.h>
#include <gui/memory.h>
#include <whb/log.h>

VPADStatus vpad;
Swkbd_CreateArg createArg;
FSClient *swkbdCli = NULL;
bool kbdVisible;

bool SWKBD_Show()
{
	WHBLogPrintf("SWKBD_Show()");
	if(kbdVisible)
		WHBLogPrintf("...while visible!!!");
	
	// Show the keyboard
	Swkbd_AppearArg appearArg;
	
	OSBlockSet(&appearArg.keyboardArg.configArg, 0, sizeof(Swkbd_ConfigArg));
	
	appearArg.keyboardArg.configArg.languageType = Swkbd_LanguageType__English;
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
	appearArg.inputFormArg.unk_0x08 = (uint32_t)NULL;
	appearArg.inputFormArg.unk_0x0C = (uint32_t)NULL;
	appearArg.inputFormArg.unk_0x14 = 0;
	appearArg.inputFormArg.unk_0x18 = 0x00008000;
	appearArg.inputFormArg.unk_0x1C = true;
	appearArg.inputFormArg.unk_0x1D = true;
	appearArg.inputFormArg.unk_0x1E = true;
	appearArg.inputFormArg.maxTextLength = -1;
	
	kbdVisible = Swkbd_AppearInputForm(appearArg);
	WHBLogPrintf("Swkbd_AppearInputForm(): %s", kbdVisible ? "true" : "false");
	if(!kbdVisible)
		return false;
	
	Swkbd_SetEnableOkButton(true);
	WHBLogPrintf("nn::swkbd::AppearInputForm success");
	return true;
}

void SWKBD_Hide()
{
	WHBLogPrintf("SWKBD_Hide()");
	if(!kbdVisible)
		WHBLogPrintf("...while invisible!!!");
	
	Swkbd_DisappearInputForm();
	kbdVisible = false;
}

void SWKBD_Render()
{
	Swkbd_ControllerInfo controllerInfo;
	controllerInfo.vpad = &vpad;
	controllerInfo.kpad[0] = NULL;
	controllerInfo.kpad[1] = NULL;
	controllerInfo.kpad[2] = NULL;
	controllerInfo.kpad[3] = NULL;
	Swkbd_Calc(controllerInfo);

	if (Swkbd_IsNeedCalcSubThreadFont())
		Swkbd_CalcSubThreadFont();

	drawKeyboard();
}

bool SWKBD_Init()
{
	WHBLogPrintf("SWKBD_Init()");
	swkbdCli = MEMAllocFromDefaultHeap(sizeof(FSClient));
	createArg.workMemory = MEMAllocFromDefaultHeap(Swkbd_GetWorkMemorySize(0));
	if(swkbdCli == NULL || createArg.workMemory == NULL)
	{
		WHBLogPrintf("SWKBD: Can't allocate memory!");
		return false;
	}
	
	FSAddClient(swkbdCli, 0);
	
	createArg.regionType = Swkbd_RegionType__Europe;
	createArg.unk_0x08 = 0;
	createArg.fsClient = swkbdCli;
	
	return Swkbd_Create(createArg);
}

void SWKBD_Shutdown()
{
	WHBLogPrintf("SWKBD_Shutdown()");
	
	if(createArg.workMemory != NULL)
	{
		Swkbd_Destroy();
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

void readInput()
{
	VPADReadError vError;
	bool run = true;
	while(run)
	{
		while(run && VPADRead(VPAD_CHAN_0, &vpad, 1, &vError) == 0)
			OSSleepTicks(1024);
		
		switch(vError)
		{
			case VPAD_READ_NO_SAMPLES:
				break;
			case VPAD_READ_INVALID_CONTROLLER:
				// TODO
			default:
				run = false;
		}
	}
}

bool showKeyboard()
{
	WHBLogPrintf("Initialising SWKBD");
	if(!SWKBD_Show())
		return false;
	
	WHBLogPrintf("SWKBD initialised successfully");
	
	while(true)
	{
		readInput();
		VPADGetTPCalibratedPoint(VPAD_CHAN_0, &vpad.tpFiltered1, &vpad.tpNormal);
		vpad.tpFiltered2 = vpad.tpNormal = vpad.tpFiltered1;
		SWKBD_Render();

		if(vpad.trigger == VPAD_BUTTON_A || vpad.trigger == VPAD_BUTTON_B)
		{
			WHBLogPrintf("SWKBD Cancel button pressed");
			SWKBD_Hide();
			return true;
		}
	}
}
