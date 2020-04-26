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
#include <coreinit/thread.h>
#include <gui/memory.h>
#include <whb/log.h>

VPADStatus vpad;
bool kbdVisible;

bool SWKBD_Show()
{
	WHBLogPrintf("SWKBD_Show()");
	if(kbdVisible)
		WHBLogPrintf("...while visible!!!");
	
	// Show the keyboard
	kbdVisible = Swkbd_AppearInputForm();
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
	Swkbd_Calc(vpad);

	if (Swkbd_IsNeedCalcSubThreadFont())
		Swkbd_CalcSubThreadFont();

	drawFrame(true);
}

bool SWKBD_Init()
{
	WHBLogPrintf("SWKBD_Init()");
	return Swkbd_Create();
}

void SWKBD_Shutdown()
{
	WHBLogPrintf("SWKBD_Shutdown()");
	Swkbd_Destroy();
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
